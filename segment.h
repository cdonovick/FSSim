#ifndef SEGMENT_H
#define SEGMENT_H
/*
 * segment.h
 *  Declaration of Segment
 */
#include "standard.h"

class Segment {
    public:
        Segment(size_t num_blocks);
        bool isDirty() const noexcept;
        double getLiveliness() const noexcept;
        
        Segment getNext();
        void setNext(Segment * next);

        void addBlock();
        void removeBLock();
    private:
        size_t num_live;
        const size_t m_num_blocks;
        Segment *m_next;
};
#endif

