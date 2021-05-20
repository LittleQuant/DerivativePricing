#include "ParkMiller.h"

const long a = 16807;
const long m = 2147483647;
const long q = 127773;
const long r = 2836;

ParkMiller::ParkMiller(long seed) : m_Seed(seed)
{
	if (seed == 0)
		m_Seed = 1;
}

void ParkMiller::SetSeed(long seed)
{
	if (seed == 0)
		seed = 1;

	m_Seed = seed;
}

ulong ParkMiller::Max()
{
	return m - 1;
}

ulong ParkMiller::Min()
{
	return 1;
}

long ParkMiller::GetOneRandomInteger()
{
	long k = m_Seed / q;
	m_Seed = a * (m_Seed - k * q) - r * k;

	if (m_Seed < 0)
		m_Seed += m;

	return m_Seed;
}



RandomParkMiller::RandomParkMiller(ulong dimensionality, ulong seed) : RandomBase(dimensionality), 
m_InnerGenerator(seed), m_InitialSeed(seed)

{
	m_Reciprocal = 1 / (1.0 + m_InnerGenerator.Max());
}

RandomBase* RandomParkMiller::clone() const
{
	return new RandomParkMiller(*this);
}

void RandomParkMiller::GetUniforms(MJArray& variates)
{
	// if had beginning and end pointer could do a std::transform(,,[](){})
	for (ulong i = 0; i < GetDimensionality(); ++i)
		variates[i] = m_InnerGenerator.GetOneRandomInteger() * m_Reciprocal;
}

void RandomParkMiller::Skip(ulong numberOfPaths)
{
	MJArray tmp(GetDimensionality());
	for (ulong i = 0; i < numberOfPaths; ++i)
		GetUniforms(tmp);
}

void RandomParkMiller::SetSeed(ulong seed)
{
	m_InitialSeed = seed;
	m_InnerGenerator.SetSeed(seed);
}

void RandomParkMiller::Reset()
{
	m_InnerGenerator.SetSeed(m_InitialSeed);
}

void RandomParkMiller::ResetDimensionality(ulong newDimensionality)
{
	RandomBase::ResetDimensionality(newDimensionality);
	m_InnerGenerator.SetSeed(m_InitialSeed);
}

