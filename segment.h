#ifndef SEGMENT_H
#define SEGMENT_H
/*
 * segment.h
 *  Declaration of Segment
 */
#include "standard.h"

class Segment {
    public:
        Segment(size_t num_blocks, Segment *next = nullptr);
        bool isDirty() const noexcept;
        double getLiveliness() const noexcept;
        
        Segment * getNext();
        void setNext(Segment *next); 

        void addLiveBlocks(size_t num); //increase num_live should not exceed m_num_blocks
        void removeLiveBlocks(size_t num); //decrease num_live should not go below 0
        size_t getFree();

    private:
        size_t num_live;
        Segment *m_next;
        const size_t m_num_blocks;
};
#endif
