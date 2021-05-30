#pragma once

#include "ExoticEngine.h"
#include "Random/Random.h"

class __declspec(dllexport) ExoticEngineBS : public ExoticEngine
{
public:
	ExoticEngineBS(const Wrapper<PathDependent>& product, const Parameters& rates, const Parameters& dividends, const Parameters& vol, const Wrapper<RandomBase>& generator, double spot);

	virtual void GetOnePath(MJArray& spotValues);
	virtual ~ExoticEngineBS() {}

private:
	Wrapper<RandomBase> m_Generator;
	MJArray m_Drifts;
	MJArray m_StandardDeviations;
	double m_LogSpot;
	ulong m_NumOfTimes;
	MJArray m_Variates;
};
