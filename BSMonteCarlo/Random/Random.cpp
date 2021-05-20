#include "Random.h"
#include "Normals.h"

RandomBase::RandomBase(ulong dimensionality) : m_Dimensionality(dimensionality) {}

void RandomBase::GetGaussians(MJArray& variates)
{
	GetUniforms(variates);

	for (ulong i = 0; i < m_Dimensionality; ++i)
	{
		double x = variates[i];
		variates[i] = InverseCumulativeNormal(x);
	}
}

void RandomBase::ResetDimensionality(ulong newDimensionality)
{
	m_Dimensionality = newDimensionality;
}