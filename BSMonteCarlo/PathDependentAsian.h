#pragma once

#include "PathDependent.h"
#include "PayOff/PayOffBridge.h"

class __declspec(dllexport) PathDependentAsian : public PathDependent
{
public:
	PathDependentAsian(const MJArray& lookAtTimes, double deliveryTime, const PayOffBridge& payOff);

	virtual ulong MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual ulong CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const;

	virtual PathDependent* clone() const;
	virtual ~PathDependentAsian() {}

private:
	double m_DeliveryTime;
	PayOffBridge m_PayOff;
	ulong m_NumberOfTimes;
};
