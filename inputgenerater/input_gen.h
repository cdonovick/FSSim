#ifndef __name_collision_wh__
#define __name_collision_whaat__

#include <cstdlib>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <set>
#include "fake_process.cpp"
#include"params.cpp"
#include <iostream>
#include <vector>
#include <ctime>
#define MEGABYTE 1000000

struct input_gen{
    //lets people chose how much pressure they want to put on the system. In reality could run it with 
    //any frame size
    
    std::vector<std::string> output;
    
    //total number of instructions 
    unsigned instructions;

    //mem_pressure is set when compared to frame size
    unsigned read;
    unsigned write;
    unsigned touch;
    unsigned grow;
    unsigned del;
    
    unsigned locality;

    //refs, start, end are set on a scale relative to each other
    unsigned size;
    unsigned range;
    

    input_gen(params p) :instructions(p.instructions), read(p.read), write(p.write), touch(p.touch), grow(p.grow), del(p.del), locality(p.locality), size(p.size), range(p.range) {}

    //to generate stuff
    void generate();
    void print_me();
};



#endif //fake_process
