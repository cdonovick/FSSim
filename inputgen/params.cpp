#ifndef __paramss__
#define __paramss__

struct params{
    int instructions;
    int read;
    int write;
	int touch; 
	int grow; 
	int del;
    int locality;
    int size;
    int range;

    bool operator==(const params & rhs){
        return ((read==rhs.read) && (write==rhs.write) && (touch==rhs.touch)&&(grow==rhs.grow)&&(del==rhs.del) && (locality==rhs.locality) && (size==rhs.size) && (range==rhs.range));    
    }
    params() :instructions(10000), read(50), write(50), touch(50), grow(50), del(50), locality(100), size(100), range(100) {}
    
};

#endif ///
