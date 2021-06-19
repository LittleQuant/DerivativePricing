#include "ImpliedVol.h"
#include "Utility/BlackScholesFormulas.h"

BSCall::BSCall(double r, double d, double T, double spot, double strike) : m_r(r), m_d(d), m_T(T), m_Spot(spot), m_Strike(strike) {}

double BSCall::operator()(double vol) const
{
	return BS::BlackScholesCall(m_Spot, m_Strike, m_r, m_d, vol, m_T);
}

BSCall2::BSCall2(double r, double d, double T, double spot, double strike) : m_r(r), m_d(d), m_T(T), m_Spot(spot), m_Strike(strike) {}

double BSCall2::Price(double vol) const
{
	return BS::BlackScholesCall(m_Spot, m_Strike, m_r, m_d, vol, m_T);
}

double BSCall2::Vega(double vol) const
{
	return BS::BlackScholesCallVega(m_Spot, m_Strike, m_r, m_d, vol, m_T);
}

