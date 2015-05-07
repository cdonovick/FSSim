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
    unsigned r_and_w;
    //refs, start, end are set on a scale relative to each other
    unsigned size;
    unsigned range;
    unsigned locality; //on a scale frome 0-100
    

    input_gen();
    input_gen(params p) : instructions(p.i), r_and_w(p.rw), size(p.s), range(p.r), locality(p.l){}

    //to generate stuff
    void generate();
    void print_me();
};



#endif //fake_process
