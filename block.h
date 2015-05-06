#ifndef BLOCK_H
#define BLOCK_H
#include "standard.h"
class Block {
    public:
        Block(); //Should init m_live to false
        ~Block();
        bool getLive() const;
        void setLive(bool b);
        virtual bool isINode() const; //should return false
    protected:
        bool m_live;
};

class Inode : public Block {
    public:
        Inode(FID fid, size_t size);
        virtual bool isINode() const; //should return true
        Block * getBlock(BlockNumber n) const;
        void setBlock(BlockNumber n, Block *b);
    private:
        std::vector<Block *> m_file_blocks; 
};

#endif

