#include "logfilesystem.h"

/*
 * Constructors and destructors
 */

/*
 * getters & setters for data members
 */
size_t LogFileSystem::getSegNum() const noexcept
{
	return m_segment_num;
}

size_t LogFileSystem::getSegSize() const noexcept
{
	return m_segment_size;
}

double LogFileSystem::getMinLife() const noexcept
{
	return m_min_life;
}

double LogFileSystem::getMinClean() const noexcept
{
	return m_min_clean;
}

void LogFileSystem::setMinLife(double min_life_val)
{
	m_min_life = min_life_val;
}

void LogFileSystem::setMinClean(double min_clean_val)
{
	m_min_clean = min_clean_val;
}


