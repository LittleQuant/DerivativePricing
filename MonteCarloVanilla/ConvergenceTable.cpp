#include "ConvergenceTable.h"

ConvergenceTable::ConvergenceTable(const Wrapper<StatisticsMC>& inner) : m_Inner(inner), m_StoppingPoint(2), m_PathsDone(0) {}

void ConvergenceTable::DumpOneResult(double result)
{
	m_Inner->DumpOneResult(result);
	++m_PathsDone;

	if (m_PathsDone == m_StoppingPoint)
	{
		m_StoppingPoint *= 2;
		std::vector<std::vector<double>> thisResult(m_Inner->GetResultsSoFar());

		for (unsigned long i = 0; i < thisResult.size(); ++i)
		{
			thisResult[i].push_back(m_PathsDone);
			m_ResultsSoFar.push_back(thisResult[i]);
		}
	}
}

StatisticsMC* ConvergenceTable::clone() const
{
	return new ConvergenceTable(*this);
}

std::vector<std::vector<double>> ConvergenceTable::GetResultsSoFar() const
{
	std::vector<std::vector<double>> tmp(m_ResultsSoFar);

	if (m_PathsDone*2 != m_StoppingPoint)
	{
		std::vector<std::vector<double>> thisResult(m_Inner->GetResultsSoFar());

		for (unsigned long i = 0; i < thisResult.size(); ++i)
		{
			thisResult[i].push_back(m_PathsDone);
			tmp.push_back(thisResult[i]);
		}
	}

	return tmp;
}