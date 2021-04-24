#include "Statistics.h"

StatisticsMC* StatisticsMean::clone() const
{
	return new StatisticsMean(*this);
}

void StatisticsMean::DumpOneResult(double result)
{
	m_PathsDone++;
	m_RunningSum += result;	
}

std::vector<std::vector<double>> StatisticsMean::GetResultsSoFar() const
{
	std::vector<std::vector<double>> results(1);
	results[0].resize(1);

	results[0][0] = m_RunningSum / m_PathsDone;

	return results;
}



