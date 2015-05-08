#ifndef LOGFILESYSTEM_H
#define LOGFILESYSTEM_H
/*
 * logfilesystem.h
 *  Declaration of the LogFileSystem
 */
#include "standard.h"
#include "segment.h"
#include <deque>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

class LogFileSystem {
    public:
        /* 
         * segment_num  - the number of segments in the file system
         * segment_size - the number of blocks in  segment
         *
         * min_life     - minimum percent liveliness before a block is scheduled for cleaning
         * min_clean    - minimum percent clean segments for the cleaner to run 
         */

        LogFileSystem(size_t segment_num, size_t segment_size, double min_life, double min_clean);
        ~LogFileSystem();

        /*
         * fid  - file id
         * size - number of blocks to allocate to file
         */
        void createFile(FID fid, size_t size);
        void growFile(FID fid, size_t size);
        void deleteFile(FID fid);

        /*
         * fid  - file id
         * n    - block of file being accessed
         */
        void deleteBlock(FID fid, BlockNumber n);
        void readBlock(FID fid, BlockNumber n);
        void writeBlock(FID fid, BlockNumber n);

        /*
         * getters - segment_num, segment_size, min_life, min_clean
         * setter - min_life, min_clean
         */
        size_t getSegNum() const noexcept;
        size_t getSegSize() const noexcept;
        double getMinLife() const noexcept;
        double getMinClean() const noexcept;

        void setMinLife(double min_life_val);
        void setMinClean(double min_clean_val);
        /*
         * Get stats functions
         * we are going to have to figure out what we want to collect
         */

        size_t getNumAccess() const noexcept;
        size_t getNumSeek() const noexcept;
    private:
        /* data */
        const size_t m_segment_num;
        const size_t m_segment_size;
        double m_min_life;
        double m_min_clean;
        
        size_t m_num_access;
        size_t m_num_seek;

        /* methods */
        void clean();
        void forceClean();
        void cleanSegment(Segment *ptr, std::unordered_map<FID, size_t> &cleaned_blocks);
        void placeCleaned(const std::unordered_map<FID, size_t> &cleaned_blocks);
        
        void pushDirty(Segment *ptr);
        void pushClean(Segment *ptr);
        void allocate(FID fid, std::deque<Segment *> fileBlocks, size_t size);
        void deleteBlock(FID fid, std::deque<Segment *> fileBlocks, BlockNumber n);
        void moveBlock(FID fid, std::deque<Segment *> fileBlocks, BlockNumber n);
        void advanceHead();
        /* internal use */
        std::vector<Segment> m_segments;
        std::unordered_map<FID, std::deque<Segment *>> m_file_map;
        
        Segment *m_head_ptr;
        Segment *m_dirty_head;

        size_t m_dirt_total;
};
#endif
