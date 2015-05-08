#include "segment.h"


Segment::Segment(size_t num_blocks, Segment *next, Segment *prev) : 
    m_next(next), m_prev(prev), m_num_blocks(num_blocks) 
{ 
}

bool Segment::isDirty() const noexcept
{
    return m_live_blocks != 0;
}

double Segment::getLiveliness() const noexcept
{
    if(m_live_blocks)
        return (m_live_blocks / m_num_blocks);
    else
        return 0;
}

Segment * Segment::getNext() const noexcept
{
    return m_next;
}

Segment * Segment::getPrev() const noexcept
{
    return m_prev;
}

void Segment::setNext(Segment *next) {
    m_next = next;
}

void Segment::setPrev(Segment *prev) {
    m_prev = prev;
}

void Segment::addLiveBlocks(FID fid, size_t num)
{
    assert(getFree() >= num);
    m_usage[fid] = m_usage[fid] + num;
    m_live_blocks += num;
}

void Segment::removeLiveBlocks(FID fid, size_t num)
{
    assert(m_live_blocks >= num);
    assert(m_usage[fid] >= num);
    m_usage[fid] = m_usage[fid] - num;
    m_live_blocks -= num;
}

size_t Segment::getFree() const 
{
    return (m_num_blocks-m_live_blocks);

}

std::unordered_map<FID, size_t> Segment::getUsage() const 
{
    return m_usage;
}
