#include "logfilesystem.h"
/*
 * Constructors and destructors
 */

LogFileSystem::LogFileSystem(size_t segment_num, size_t segment_size, double min_life, double min_clean) : 
    m_segment_num(segment_num), m_segment_size(segment_size), m_min_life(min_life), m_min_clean(min_clean),
    m_num_access(0), m_num_seek(0), m_dirty_head(nullptr), m_dirt_total(0)
{    
    for(size_t i = 0; i < m_segment_num; ++i) {
        m_segments.emplace_back(m_segment_size);
    }

    for(size_t i = 1; i < segment_num - 1; ++i) {
        m_segments[i].setPrev(&m_segments[i-1]);
        m_segments[i].setNext(&m_segments[i+1]);
    }

    m_segments[segment_num-1].setPrev(&m_segments[segment_num-2]);
    m_segments[0].setNext(&m_segments[1]);

    m_head_ptr = &m_segments[0];

}
LogFileSystem::~LogFileSystem() {}

/*
 * getters & setters for data members
 */
size_t LogFileSystem::getSegNum() const noexcept
{
    return m_segment_num;
}

size_t LogFileSystem::getSegSize() const noexcept
{
    return m_segment_size;
}

double LogFileSystem::getMinLife() const noexcept
{
    return m_min_life;
}

double LogFileSystem::getMinClean() const noexcept
{
    return m_min_clean;
}

void LogFileSystem::setMinLife(double min_life_val)
{
    m_min_life = min_life_val;
}

void LogFileSystem::setMinClean(double min_clean_val)
{
    m_min_clean = min_clean_val;
}

size_t LogFileSystem::getNumAccess() const noexcept
{
    return m_num_access;
}

size_t LogFileSystem::getNumSeek() const noexcept
{
    return m_num_seek;
}


void LogFileSystem::createFile(FID fid, size_t size) 
{

    ++m_num_access;
    std::deque<Segment *> fileBlocks = m_file_map[fid];
    assert (fileBlocks.empty());
    /* n + 1 for INode */
    allocate(fid, fileBlocks, size + 1);
    assert (fileBlocks.size() == size + 1);
    m_file_map[fid] = fileBlocks;
    clean();
}

void LogFileSystem::growFile(FID fid, size_t size) 
{

    ++m_num_access;
    std::deque<Segment *> fileBlocks = m_file_map[fid];
    assert (!fileBlocks.empty());
    allocate(fid, fileBlocks, size);
    /* update INode */
    moveBlock(fid, fileBlocks, 0);
    m_file_map[fid] = fileBlocks;
    clean();
}

void LogFileSystem::deleteFile(FID fid) 
{

    ++m_num_access;
    std::deque<Segment *> fileBlocks = m_file_map[fid];
    assert (!fileBlocks.empty());
    while(!fileBlocks.empty()) {
        deleteBlock(fid, fileBlocks, 0);
    }
    m_file_map[fid] = fileBlocks;
}


void LogFileSystem::allocate(FID fid, std::deque<Segment *> &fileBlocks, size_t size)
{
    while(size > 0) {
        while (m_head_ptr->getFree() && size > 0) {
            fileBlocks.push_back(m_head_ptr);
            m_head_ptr->addLiveBlocks(fid, 1);
            --size;
        }
        if (size > 0) {
            ++m_num_seek;
            assert(m_head_ptr->getFree() == 0);
            advanceHead();
        }
    }
}

void LogFileSystem::deleteBlock(FID fid, BlockNumber n)
{
    ++m_num_access;
    std::deque<Segment *> fileBlocks = m_file_map[fid];
    /* n + 1 for INode */
    deleteBlock(fid, fileBlocks, n + 1);
    m_file_map[fid] = fileBlocks;
    clean();
}

void LogFileSystem::readBlock(FID fid, BlockNumber n)
{
    ++m_num_access;
    m_num_seek += m_file_map[fid][n] != m_head_ptr; 
    
}

void LogFileSystem::writeBlock(FID fid, BlockNumber n)
{
    ++m_num_access;
    std::deque<Segment *> fileBlocks = m_file_map[fid];
    std::cout << fileBlocks.size() << std::endl;
    /* n + 1 for INode */
    moveBlock(fid, fileBlocks, n + 1);

    /* update INode */
    moveBlock(fid, fileBlocks, 0);

    m_file_map[fid] = fileBlocks;
    clean();
}

void LogFileSystem::clean() 
{
    if ((m_segment_num -  m_dirt_total)/static_cast<double>(m_segment_num) >= m_min_life) {
        return;
    }

    std::unordered_map<FID, size_t> cleaned_blocks;
    for (auto ptr = m_dirty_head; ptr != nullptr; ptr = ptr->getNext()) {
        if (ptr->getLiveliness() < m_min_clean) {
            cleanSegment(ptr, cleaned_blocks);
        }
    }

}

void LogFileSystem::forceClean() 
{

    std::unordered_map<FID, size_t> cleaned_blocks;
    for (auto ptr = m_dirty_head; ptr != nullptr; ptr = ptr->getNext()) {
        cleanSegment(ptr, cleaned_blocks);
    }

}

void LogFileSystem::cleanSegment(Segment *ptr, std::unordered_map<FID, size_t> &cleaned_blocks)
{
    auto usage = ptr->getUsage();
    for (auto i: usage) {
        auto file = m_file_map[i.first];
        auto segment = std::find(file.begin(), file.end(), ptr);
        assert(segment != file.end());
        deleteBlock(i.first, file, segment - file.begin());
        cleaned_blocks[i.first]++;
    }
}

void LogFileSystem::placeCleaned(const std::unordered_map<FID, size_t> &cleaned_blocks) 
{
    for (auto i: cleaned_blocks) {
        auto fileBlocks = m_file_map[i.first];
        allocate(i.first, fileBlocks, i.second); 
        /* update INode */
        moveBlock(i.first, fileBlocks, 0);
    }
}


void LogFileSystem::pushDirty(Segment *ptr) 
{
    auto p = ptr->getPrev();
    auto n = ptr->getNext();
    if (p != nullptr) {
        p->setNext(n);
    }
    if (n != nullptr) {
        n->setPrev(p);
    }

    ptr->setNext(m_dirty_head);
    ptr->setPrev(nullptr);

    if (m_dirty_head != nullptr) {
        m_dirty_head->setPrev(ptr);
    }

    m_dirty_head = ptr;
}

void LogFileSystem::pushClean(Segment *ptr) 
{
    auto p = ptr->getPrev();
    auto n = ptr->getNext();
    if (p != nullptr) {
        p->setNext(n);
    }
    if (n != nullptr) {
        n->setPrev(p);
    }

    ptr->setNext(m_head_ptr->getNext());
    ptr->setPrev(m_head_ptr);

    if (m_head_ptr->getNext() != nullptr) {
        m_head_ptr->getNext()->setPrev(ptr);
    }

    m_head_ptr->setNext(ptr);
    m_dirt_total--;
}

void LogFileSystem::deleteBlock(FID fid, std::deque<Segment *> &fileBlocks, BlockNumber n)
{
    /* block to be deleted */
    assert (fileBlocks.size() > n);
    m_num_seek += m_file_map[fid][n] != m_head_ptr; 
    fileBlocks[n]->removeLiveBlocks(fid, 1);
    if (!fileBlocks[n]->isDirty()) {
        pushClean(fileBlocks[n]);
    }
    fileBlocks.erase(fileBlocks.begin() + n);
}


void LogFileSystem::moveBlock(FID fid, std::deque<Segment *> &fileBlocks, BlockNumber n)
{
    m_num_seek += m_file_map[fid][n] != m_head_ptr; 
    assert(fileBlocks.size() > n);
    if (!m_head_ptr->getFree()) {
        advanceHead();
    }

    fileBlocks[n]->removeLiveBlocks(fid, 1);
    if (!fileBlocks[n]->isDirty()) {
        pushClean(fileBlocks[n]);
    }

    fileBlocks[n] = m_head_ptr;
    m_head_ptr->addLiveBlocks(fid, 1);
}

void LogFileSystem::advanceHead() 
{
    auto ptr = m_head_ptr->getNext();
    if (ptr == nullptr) {
        forceClean();
        ptr = m_head_ptr->getNext();
        assert(ptr != nullptr);
    }
    pushDirty(m_head_ptr);
    m_head_ptr = ptr;
    ++m_dirt_total;
}
