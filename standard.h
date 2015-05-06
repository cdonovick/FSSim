#ifndef STANDARD_H
#define STANDARD_H
/*
 * standard.h 
 *  common includes and typdefs
 *
 */
#include <cstddef>
#include <vector>
#include <utility>

typedef size_t FID;
typedef size_t SegmentNumber;
typedef size_t BlockNumber;

enum Block {
    dead,
    live
};


#endif

