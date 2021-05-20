#pragma once

#include "Statistics.h"
#include "../Utility/Wrapper.h"

class __declspec(dllexport) ConvergenceTable : public StatisticsMC
{
public:
	ConvergenceTable(const Wrapper<StatisticsMC>& inner);
	
	virtual void DumpOneResult(double result);
	virtual StatisticsMC* clone() const;
	virtual std::vector<std::vector<double>> GetResultsSoFar() const;
private:
	Wrapper<StatisticsMC> m_Inner;
	std::vector<std::vector<double>> m_ResultsSoFar;
	unsigned long m_StoppingPoint;
	unsigned long m_PathsDone;
};