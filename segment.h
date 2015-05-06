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
        bool isDirty() const noexcept;
        double getLiveliness() const noexcept;
        SegmentNumber getSegmentNumber() const noexcept;

        void addBlock();
        void removeBLock();
    private:
        const SegmentNumber m_idx;
        size_t num_live;
        const size_t m_num_blocks;
        Segment *m_next;
};
#endif

