#ifndef SEGMENT_H
#define SEGMENT_H
/*
 * segment.h
 *  Declaration of Segment
 */
#include "standard.h"

class Segment {
    public:
        Segment(SegmentNumber n, size_t num_blocks);
        
        bool isDirty(void) const noexcept;
        double getLiveliness(void) const noexcept;


        void setBlock(BlockNumber n, Block b);
        Block getBlock(BlockNumber n) const;
        SegmentNumber getSegmentNumber;
    private:
        std::vector<Block> m_blocks;
        Segment *m_next;
        bool m_is_dirty;
        SegmentNumber m_idx;
};
#endif

