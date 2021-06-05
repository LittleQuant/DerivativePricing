#include "Barrier.h"

Barrier::Barrier(const MJArray& lookAtTimes, double deliveryTime, double barrier, bool out, bool up, const PayOffBridge& payOff, double rebate)
	: PathDependent(lookAtTimes), m_DeliveryTime(deliveryTime), m_Barrier(barrier), m_Out(out), m_Up(up), m_PayOff(payOff), m_Rebate(rebate), m_NumberOfTimes(lookAtTimes.size()) {}

bool Barrier::operator()(double spotValue) const
{
	if (m_Up)
		return spotValue >= m_Barrier;
	else
		return spotValue <= m_Barrier;
}

ulong Barrier::MaxNumberOfCashFlows() const
{
	return 1UL;
}

MJArray Barrier::PossibleCashFlowTimes() const
{
	MJArray tmp(1UL);
	tmp[0] = m_DeliveryTime;
	return tmp;
}

ulong Barrier::CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const
{
	bool hit = false;

	ulong i = 0;
	while (!hit && i < m_NumberOfTimes)
	{
		hit = (*this)(spotValues[i]);
		i++;
	}

	generatedCashFlows[0].m_TimeIndex = 0UL;
	double nonRebated = m_PayOff(spotValues[m_NumberOfTimes - 1]);
	double rebated = m_Rebate * nonRebated;

	if (m_Out)
	{
		generatedCashFlows[0].m_Amount = hit ? rebated : nonRebated;
	}
	else
	{
		generatedCashFlows[0].m_Amount = hit ? nonRebated : rebated;
	}
		
	return 1UL;
}

PathDependent* Barrier::clone() const
{
	return new Barrier(*this);
}


