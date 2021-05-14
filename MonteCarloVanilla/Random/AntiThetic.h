#pragma once

#include "Random.h"
#include "../Wrapper.h"

class AntiThetic : public RandomBase
{
public:
	AntiThetic(const Wrapper<RandomBase>& innerGenerator);
	virtual RandomBase* clone() const;
	virtual void GetUniforms(MJArray& variates);
	virtual void Skip(ulong numberOfPaths);
	virtual void SetSeed(ulong seed);
	virtual void ResetDimensionality(ulong newDimensionality);
	virtual void Reset();
private:
	Wrapper<RandomBase> m_InnerGenerator;	// copy of the original generator to not affect the original's seed
	bool m_IsEven;
	MJArray m_NextVariates;
};
