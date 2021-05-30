#include "PathDependent.h"

PathDependent::PathDependent(const MJArray& lookAtTimes) : m_LookAtTimes(lookAtTimes) {}

const MJArray& PathDependent::GetLookAtTimes() const
{
	return m_LookAtTimes;
}

PathDependent::~PathDependent() {}