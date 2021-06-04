#include "ExoticEngine.h"

ExoticEngine::ExoticEngine(const Wrapper<PathDependent>& product, const Parameters& rates) : m_Product(product), m_Rates(rates), m_Discounts(product->PossibleCashFlowTimes()) 
{
	for (ulong i = 0; i < m_Discounts.size(); ++i)
	{
		m_Discounts[i] = exp(-m_Rates.Integral(0.0, m_Discounts[i]));
	}

	m_CashFlows.resize(m_Product->MaxNumberOfCashFlows());
	
}

void ExoticEngine::DoSimulation(StatisticsMC& gatherer, ulong numPaths)
{
	MJArray spotValues(m_Product->GetLookAtTimes().size());

	m_CashFlows.resize(m_Product->MaxNumberOfCashFlows());
	double thisValue = 0;

	for (ulong i = 0; i < numPaths; ++i)
	{
		GetOnePath(spotValues);
		thisValue = DoOnePath(spotValues);
		gatherer.DumpOneResult(thisValue);
	}
}

double ExoticEngine::DoOnePath(const MJArray& spotValues) const
{
	ulong numberFlows = m_Product->CashFlows(spotValues, m_CashFlows);

	double value = 0.0;

	for (ulong i = 0; i < numberFlows; ++i)
	{
		value += m_CashFlows[i].m_Amount * m_Discounts[m_CashFlows[i].m_TimeIndex];
	}

	return value;
}

ExoticEngine::~ExoticEngine() {}