#ifndef __paramss__
#define __paramss__

struct params{
    int i;
    int rw;
	int s; 
	int r; 
	int l;
    bool operator==(const params & rhs){
        return ((i==rhs.i) && (rw==rhs.rw) && (s=rhs.s) && (r==rhs.r) && (r==rhs.r));    
    }
    params() :i(1000), rw(50), s(500), r(1000), l(20){} 
    
};

#endif ///
