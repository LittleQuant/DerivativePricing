#pragma once

#include "PathDependent.h"
#include "../PayOff/PayOffBridge.h"

class __declspec(dllexport) Barrier : public PathDependent
{
public:
	Barrier(const MJArray& lookAtTimes, double deliveryTime, double barrier, bool out, bool up, const PayOffBridge& payOff, double rebate = 0.0);

	virtual ulong MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual ulong CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const;
	
	virtual PathDependent* clone() const;
	virtual ~Barrier() {}

private:
	double m_DeliveryTime;
	double m_Barrier;
	double m_Rebate;
	bool m_Out;
	bool m_Up;
	PayOffBridge m_PayOff;
	ulong m_NumberOfTimes;

	bool operator()(double spotValue) const;
};


