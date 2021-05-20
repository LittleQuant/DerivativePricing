#include "AntiThetic.h"

AntiThetic::AntiThetic(const Wrapper<RandomBase>& innerGenerator) : RandomBase(*innerGenerator), m_InnerGenerator(innerGenerator)
{
	m_InnerGenerator->Reset();
	m_IsEven = true;
	m_NextVariates.resize(GetDimensionality());
}

RandomBase* AntiThetic::clone() const
{
	return new AntiThetic(*this);
}

void AntiThetic::GetUniforms(MJArray& variates)
{
	if (m_IsEven)
	{
		m_InnerGenerator->GetUniforms(variates);
		for (ulong i = 0; i < GetDimensionality(); ++i)
			m_NextVariates[i] = 1.0 - variates[i];

		m_IsEven = false;
	}
	else
	{
		variates = m_NextVariates;
		m_IsEven = true;
	}
}

void AntiThetic::SetSeed(ulong seed)
{
	m_InnerGenerator->SetSeed(seed);
	m_IsEven = true;
}

void AntiThetic::Skip(ulong numberOfPaths)
{
	if (numberOfPaths == 0)
		return;
	
	if (m_IsEven)
	{
		m_IsEven = false;
		numberOfPaths--;
	}
	m_InnerGenerator->Skip(numberOfPaths / 2);

	if (numberOfPaths % 2)
	{
		MJArray tmp(GetDimensionality());
		GetUniforms(tmp);
	}
}

void AntiThetic::ResetDimensionality(ulong newDimensionality)
{
	RandomBase::ResetDimensionality(newDimensionality);
	m_NextVariates.resize(newDimensionality);
	m_InnerGenerator->ResetDimensionality(newDimensionality);
}

void AntiThetic::Reset()
{
	m_InnerGenerator->Reset();
	m_IsEven = true;
}