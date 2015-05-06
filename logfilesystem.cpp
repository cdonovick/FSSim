#include "logfilesystem.h"
using namespace std;

/*
 * Constructors and destructors
 */

/*
 * getters & setters for data members
 */
size_t LogFileSystem::get_seg_num()
{
  return m_segment_num;
}

size_t LogFileSystem::get_seg_size()
{
  return m_segment_size;
}

double LogFileSystem::get_min_life()
{
  return m_min_life;
}

double LogFileSystem::get_min_clean()
{
  return m_min_clean;
}

void LogFileSystem::set_min_life(double min_life_val)
{
  m_min_life = min_life_val;
}

void LogFileSystem::set_min_clean(double min_clean_val)
{
  m_min_clean = min_clean_val;
}


