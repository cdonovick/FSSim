#ifndef LOGFILESYSTEM_H
#define LOGFILESYSTEM_H
/*
 * logfilesystem.h
 *  Declaration of the LogFileSystem
 */
#include "standard.h"
#include "segment.h"

class LogFileSystem {
    public:
        /* 
         * segment_num  - the number of segments in the file system
         * segment_size - the number of blocks in  segment
         *
         * min_life     - minimum percent liveliness before a block is scheduled for cleaning
         * min_clean    - minimum percent clean segments for the cleaner to run 
         */

				//Just change this constructor if its not done right
        LogFileSystem(size_t segment_num, size_t segment_size, double min_life, double min_clean) 
					: m_segment_num(segment_num), 
						m_segment_size(segment_size),
						m_min_life(min_life),
						m_min_clean(min_clean){ }

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
        void readBlock(FID fid, BlockNumber n);
        void writeBlock(FID fid, BlockNumber n);
        void deleteBlock(FID fid, BlockNumber n);

        /*
         * getters - segment_num, segment_size, min_life, min_clean
         * setter - min_life, min_clean
         */
				size_t get_seg_num();
				size_t get_seg_size();
				double get_min_life();
				double get_min_clean();
				void set_min_life(double min_life_val);
				void set_min_clean(double min_clean_val);
        /*
         * Get stats functions
         * we are going to have to figure out what we want to collect
         */
    protected:        
        
        /* data */
        const size_t m_segment_num;
        const size_t m_segment_size;
        double m_min_life;
        double m_min_clean;

        std::vector<Segment> m_segments;
        
        Segment *m_head_ptr;
        size_t m_head_idx;

        Segment *m_clean_tail;

        Segment *m_dirty_head;
        size_t m_dirt_num;


        /* methods */
        Block lookup(SegmentNumber a, BlockNumber b);
        void clean();
};
#endif
