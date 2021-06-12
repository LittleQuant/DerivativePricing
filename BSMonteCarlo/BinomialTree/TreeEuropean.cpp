#include "TreeEuropean.h"

TreeEuropean::TreeEuropean(double finalTime, const PayOffBridge& payOff) : TreeProduct(finalTime), m_PayOff(payOff) {}

TreeProduct* TreeEuropean::clone() const
{
	return new TreeEuropean(*this);
}

double TreeEuropean::FinalPayOff(double spot) const
{
	return m_PayOff(spot);
}

double TreeEuropean::PreFinalPayOff(double spot, double time, double discountedFutureValues) const
{
	return discountedFutureValues;
}