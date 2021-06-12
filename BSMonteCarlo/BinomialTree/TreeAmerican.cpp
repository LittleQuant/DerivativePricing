#include "TreeAmerican.h"

#include <algorithm>

TreeAmerican::TreeAmerican(double finalTime, const PayOffBridge& payOff) : TreeProduct(finalTime), m_PayOff(payOff) {}

TreeProduct* TreeAmerican::clone() const
{
	return new TreeAmerican(*this);
}

double TreeAmerican::FinalPayOff(double spot) const
{
	return m_PayOff(spot);
}

double TreeAmerican::PreFinalPayOff(double spot, double time, double discountedFutureValues) const
{
	return std::max(m_PayOff(spot), discountedFutureValues);
}