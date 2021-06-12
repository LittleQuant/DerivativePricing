#pragma once

#include "../Utility/Parameters.h"
#include "PathDependent.h"
#include "../Statistics/Statistics.h"
#include "../Utility/Wrapper.h"

#include <vector>

class __declspec(dllexport) ExoticEngine
{
public:
	ExoticEngine(const Wrapper<PathDependent>& product, const Parameters& rates);

	virtual void GetOnePath(MJArray& spotValues) = 0;
	void DoSimulation(StatisticsMC& gatherer, ulong numPaths);
	double DoOnePath(const MJArray& spotValues) const;

	virtual ~ExoticEngine();

private:
	Wrapper<PathDependent> m_Product;
	Parameters m_Rates;
	MJArray m_Discounts;
	mutable std::vector<CashFlow> m_CashFlows;


};
