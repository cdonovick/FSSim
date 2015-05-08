#ifndef SEGMENT_H
#define SEGMENT_H
/*
 * segment.h
 *  Declaration of Segment
 */
#include "standard.h"
#include <vector>
#include <unordered_map>
class Segment {
    public:
        Segment(size_t num_blocks, Segment *next = nullptr, Segment *prev = nullptr);
        bool isDirty() const noexcept;
        double getLiveliness() const noexcept;

        Segment * getNext() const noexcept;
        Segment * getPrev() const noexcept;
        void setNext(Segment *next); 
        void setPrev(Segment *prev);
        void addLiveBlocks(FID fid, size_t num); //increase num_live should not exceed m_num_blocks
        void removeLiveBlocks(FID fid, size_t num); //decrease num_live should not go below 0
        size_t getFree() const;

        std::unordered_map<FID, size_t> getUsage() const; 
    private:
        Segment *m_next;
        Segment *m_prev;
        const size_t m_num_blocks;
        size_t m_live_blocks;
        std::unordered_map<FID, size_t> m_usage;
};
#endif
