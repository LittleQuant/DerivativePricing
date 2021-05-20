#pragma once

// Using arrays instead of vectors for the moment due to following closely Mark Joshi

#include "../Utility/Arrays.h"

typedef unsigned long ulong;

class __declspec(dllexport) RandomBase
{
public:
	RandomBase(ulong dimensionality);
	virtual RandomBase* clone() const = 0;
	
	inline ulong GetDimensionality() const;
	virtual void GetUniforms(MJArray& variates) = 0;
	virtual void Skip(ulong numberOfPaths) = 0;
	virtual void SetSeed(ulong seed) = 0;
	virtual void Reset() = 0;

	virtual void GetGaussians(MJArray& variates);
	virtual void ResetDimensionality(ulong newDimensionality);

private:
	ulong m_Dimensionality;
};

ulong RandomBase::GetDimensionality() const
{
	return m_Dimensionality;
}
