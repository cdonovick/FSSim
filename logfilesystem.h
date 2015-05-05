#ifndef LOGFILESYSTEM_H
#define LOGFILESYSTEM_H
#include "standard.h"

class LogFileSystem {
    public:
        typedef unsigned int FID;


        /* 
         * capacity     - the number of segements in the file system
         * segment_size - the number of blocks in  segment
         *
         * min_life     - minimum percent livelness before a block is scheduled for cleaning
         * min_clean    - minimum percent clean segements for the cleaner to run 
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
        void writeFile(fid fid, int change);
        void readFile(FID fid);

        /*
         * Get stats functions
         * we are going to have to figure out what we want to collect
         */
};
#endif

