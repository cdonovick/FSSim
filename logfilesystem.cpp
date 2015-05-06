#include "logfilesystem.h"

/*
 * Constructors and destructors
 */

LogFileSystem::LogFileSystem(size_t segment_num, size_t segment_size, double min_life, double min_clean)
			: m_segment_num(segment_num), m_segment_size(segment_size), m_min_life(min_life), m_min_clean(min_clean)
{    
        m_segments.emplace_back(m_segment_size);
        for(size_t i = 1; i < m_segment_num; ++i) {
            m_segments.emplace_back(m_segment_size, &m_segments[i-1]);
        }

        m_head_ptr = &m_segments[0];
        m_clean_tail = &m_segments[m_segment_num - 1];
		m_dirty_head = nullptr;
        m_dirt_num = 0;
}


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


void LogFileSystem::createFile(FID fid, size_t size) 
{
    std::vector<Segment *> fileBlocks = m_file_map[fid];
    assert (fileBlocks.empty());
    while(size > 0) {
        if (m_head_ptr->getFree() > size) {
            m_head_ptr->addLiveBlocks(size);
            size = 0;
            fileBlocks.insert(fileBlocks.end(), size, m_head_ptr);
        } else {
            size_t temp = m_head_ptr->getFree();
            m_head_ptr->addLiveBlocks(temp);
            fileBlocks.insert(fileBlocks.end(), temp, m_head_ptr);
            size -= temp;
            m_head_ptr = m_head_ptr->getNext();
        }
    }
}

void LogFileSystem::growFile(FID fid, size_t size) 
{

}

void LogFileSystem::deleteFile(FID fid) 
{

}
