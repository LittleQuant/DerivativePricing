#include "pch.h"

#include "PayOff.h"

#include <algorithm>
#include <cmath>

// Vanilla Options
PayOffCall::PayOffCall(double strike) : m_Strike(strike) {}

double PayOffCall::operator()(double spot) const
{
	return (std::max)(spot - m_Strike, 0.0);
}

PayOff* PayOffCall::clone() const
{
	return new PayOffCall(*this);
}



PayOffPut::PayOffPut(double strike) : m_Strike(strike) {}

double PayOffPut::operator()(double spot) const
{
	return (std::max)(m_Strike - spot, 0.0);
}

PayOff* PayOffPut::clone() const
{
	return new PayOffPut(*this);
}



PayOffDoubleDigital::PayOffDoubleDigital(double lowerStrike, double upperStrike) : m_LowerStrike(lowerStrike), m_UpperStrike(upperStrike) {}

double PayOffDoubleDigital::operator() (double spot) const
{
	return (int)(m_LowerStrike < spot < m_UpperStrike);
}

PayOff* PayOffDoubleDigital::clone() const
{
	return new PayOffDoubleDigital(*this);
}


// Power
PayOffPowerCall::PayOffPowerCall(double strike, double power) : m_Strike(strike), m_Power(power) {}

double PayOffPowerCall::operator() (double spot) const
{
	return (std::max)(pow(spot, m_Power) - m_Strike, 0.0);
}

PayOff* PayOffPowerCall::clone() const
{
	return new PayOffPowerCall(*this);
}



PayOffPowerPut::PayOffPowerPut(double strike, double power) : m_Strike(strike), m_Power(power) {}

double PayOffPowerPut::operator() (double spot) const
{
	return (std::max)(m_Strike - pow(spot, m_Power), 0.0);
}

PayOff* PayOffPowerPut::clone() const
{
	return new PayOffPowerPut(*this);
}