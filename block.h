#ifndef BLOCK_H
#define BLOCK_H
#include "standard.h"
class Block {
    public:
        Block(Block *p); //Should init m_live to false
        ~Block();
        bool getLive() const noexcept;
        void setLive(bool b);
        Block * getParent() const noexcept;
        void setParent(Block *p);
    protected:
        bool m_live;
        Block *parent;
};

class INode : public Block {
    public:
        INode(FID fid, size_t size);
        Block * getBlock(BlockNumber n);
        void setBlock(BlockNumber n, Block *b);
    private:
        std::vector<Block *> m_file_blocks;
};

#endif

