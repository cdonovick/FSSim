#ifndef LOGFILESYSTEM_H
#define LOGFILESYSTEM_H
/*
 * logfilesystem.h
 *  Declaration of the LogFileSystem
 */
#include "standard.h"

class LogFileSystem {
    public:


        /* 
         * capacity     - the number of segments in the file system
         * segment_size - the number of blocks in  segment
         *
         * min_life     - minimum percent liveliness before a block is scheduled for cleaning
         * min_clean    - minimum percent clean segments for the cleaner to run 
         */
        LogFileSystem(size_t capacity, size_t segment_size, double min_life, double min_clean);

        ~LogFileSystem();

        /*
         * fid      - file id,
         * size     - number of blocks in the file
         * change   - change in file size, can be 0
         */
        void createFile(FID fid, size_t size);
        void deleteFile(FID fid);
        void writeFile(FID fid, int change);
        void readFile(FID fid);

        /*
         * Get stats functions
         * we are going to have to figure out what we want to collect
         */


    protected:
        typedef bool block; 

        struct segment {
            std::vector<block> blocks;
            segment *next;
        };
};
#endif

