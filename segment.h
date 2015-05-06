#ifndef SEGMENT_H
#define SEGMENT_H
/*
 * segment.h
 *  Declaration of Segment
 */
#include "standard.h"
#include "block.h"

class Segment {
    public:
        Segment(SegmentNumber n, size_t num_blocks, Block *blocks);        
        bool isDirty() const noexcept;
        double getLiveliness() const noexcept;
        SegmentNumber getSegmentNumber() const noexcept;
        Block * getBlock(BlockNumber n) const;
    private:
        const SegmentNumber m_idx;
        bool m_is_dirty; //True if any block is live
        const size_t m_num_blocks;
        const Block *m_blocks;
        Segment *m_next;
};
#endif

