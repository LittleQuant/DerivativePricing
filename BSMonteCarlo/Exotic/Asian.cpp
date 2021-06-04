#include "Asian.h"

#include <iostream>

// Asian interface

Asian::Asian(const MJArray& lookAtTimes, double deliveryTime, const PayOffBridge& payOff)
	: PathDependent(lookAtTimes), m_DeliveryTime(deliveryTime), m_PayOff(payOff), m_NumberOfTimes(lookAtTimes.size()) {}

ulong Asian::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray Asian::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = m_DeliveryTime;
	return tmp;
}


// Arithmetic Asian

AsianArithmetic::AsianArithmetic(const MJArray& lookAtTimes, double deliveryTime, const PayOffBridge& payOff) : Asian(lookAtTimes, deliveryTime, payOff) {}

ulong AsianArithmetic::CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const
{
	double sum = spotValues.sum();
	double mean = sum / m_NumberOfTimes;

	generatedCashFlows[0].m_TimeIndex = 0UL;
	generatedCashFlows[0].m_Amount = m_PayOff(mean);

	return 1UL;
}

PathDependent* AsianArithmetic::clone() const
{
	return new AsianArithmetic(*this);
}


// Geometric Asian

AsianGeometric::AsianGeometric(const MJArray& lookAtTimes, double deliveryTime, const PayOffBridge& payOff) : Asian(lookAtTimes, deliveryTime, payOff) {}

ulong AsianGeometric::CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const
{
	double prod = spotValues.prod();	// this will reduce the value of the option as we encounter 0s in our expectation
	double mean = pow(prod, 1.0 / m_NumberOfTimes);
	
	generatedCashFlows[0].m_TimeIndex = 0UL;
	generatedCashFlows[0].m_Amount = m_PayOff(mean);

	return 1UL;
}

PathDependent* AsianGeometric::clone() const
{
	return new AsianGeometric(*this);
}
