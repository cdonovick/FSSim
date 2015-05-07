#include "segment.h"
using namespace std;


Segment::Segment(size_t num_blocks, Segment *next)
: m_next(next), m_num_blocks(num_blocks)
{
	num_live = 0;
}
/* Need to decide what constitutes a dirty block:
* 
*
*/
bool Segment::isDirty() const noexcept
{
	if(num_live >0)
		return true;
	else
		return false;
}

double Segment::getLiveliness() const noexcept
{
	if(num_live > 0)
		return (num_live / m_num_blocks);
	else
		return 0;
}

Segment * Segment::getNext()
{
	return m_next;
}

void Segment::addLiveBlocks(size_t num)
{
	num_live += num;

}

void Segment::removeLiveBlocks(size_t num)
{
	num_live -= num;

}

size_t Segment::getFree()
{
	return (m_num_blocks-num_live);

}
