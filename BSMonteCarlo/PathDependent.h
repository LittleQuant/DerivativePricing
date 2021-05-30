#pragma once

#include "Utility/Arrays.h"

#include <vector>

class CashFlow
{
public:
	CashFlow(ulong timeIndex = 0UL, double amount = 0.0) : m_TimeIndex(timeIndex), m_Amount(amount) {}

	ulong m_TimeIndex;
	double m_Amount;
};

class __declspec(dllexport) PathDependent
{
public:
	PathDependent(const MJArray& lookAtTimes);

	const MJArray& GetLookAtTimes() const;

	virtual ulong MaxNumberOfCashFlows() const = 0;
	virtual MJArray PossibleCashFlowTimes() const = 0;
	virtual ulong CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const = 0;

	virtual PathDependent* clone() const = 0;
	virtual  ~PathDependent();

private:
	MJArray m_LookAtTimes;
};