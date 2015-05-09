#ifndef __fake__process__
#define __fake__process__

struct fake_process{
    unsigned location;
    unsigned size;
    fake_process(unsigned _location, unsigned _size) : location(_location), size(_size) {}
   
    bool operator<(const fake_process & rhs) const{
        return (size< rhs.size);
    } 
    bool operator==(const fake_process & rhs) const{
        return (location == rhs.location);
    }
};

#endif //dfa

