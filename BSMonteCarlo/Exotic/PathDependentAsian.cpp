#include "PathDependentAsian.h"

PathDependentAsian::PathDependentAsian(const MJArray& lookAtTimes, double deliveryTime, const PayOffBridge& payOff)
	: PathDependent(lookAtTimes), m_DeliveryTime(deliveryTime), m_PayOff(payOff), m_NumberOfTimes(lookAtTimes.size()) {}

ulong PathDependentAsian::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray PathDependentAsian::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = m_DeliveryTime;
	return tmp;
}

ulong PathDependentAsian::CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const
{
	double sum = spotValues.sum();
	double mean = sum / m_NumberOfTimes;

	generatedCashFlows[0].m_TimeIndex = 0UL;
	generatedCashFlows[0].m_Amount = m_PayOff(mean);

	return 1UL;
}

PathDependent* PathDependentAsian::clone() const
{
	return new PathDependentAsian(*this);
}