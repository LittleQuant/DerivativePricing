#include "Vanilla.h"

VanillaOption::VanillaOption(const PayOffBridge& payOff, double expiry) : m_PayOff(payOff), m_Expiry(expiry) {}

double VanillaOption::optionPayOff(double spot) const
{
	return m_PayOff(spot);
}

double VanillaOption::getExpiry() const
{
	return m_Expiry;
}

