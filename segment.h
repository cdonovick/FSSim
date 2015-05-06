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
        Segment(SegmentNumber n, size_t num_blocks);
        
        bool isDirty(void) const noexcept;
        double getLiveliness(void) const noexcept;
        SegmentNumber getSegmentNumber() const noexcept;

        void setBlock(BlockNumber n, Block b);
        Block getBlock(BlockNumber n) const;
    private:
        const SegmentNumber m_idx;
        bool m_is_dirty; //True if any block is live

        std::vector<Block> m_blocks;
        Segment *m_next;
};
#endif

