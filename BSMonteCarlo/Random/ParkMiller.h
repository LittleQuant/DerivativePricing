#pragma once

#include "Random.h"

class ParkMiller
{
public:
	ParkMiller(long seed = 1);

	long GetOneRandomInteger();
	void SetSeed(long seed);

	static ulong Max();
	static ulong Min();

private:
	long m_Seed;
};

class __declspec(dllexport) RandomParkMiller : public RandomBase
{
public:
	RandomParkMiller(ulong dimensionality, ulong seed = 1);

	virtual RandomBase* clone() const;
	virtual void GetUniforms(MJArray& variates);
	virtual void Skip(ulong numberOfPaths);
	virtual void SetSeed(ulong seed);
	virtual void Reset();
	virtual void ResetDimensionality(ulong newDimensionality);

private:
	ParkMiller m_InnerGenerator;
	ulong m_InitialSeed;
	double m_Reciprocal;
};