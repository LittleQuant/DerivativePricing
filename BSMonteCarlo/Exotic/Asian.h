#pragma once

#include "PathDependent.h"
#include "../PayOff/PayOffBridge.h"

class __declspec(dllexport) Asian : public PathDependent
{
public:
	Asian(const MJArray& lookAtTimes, double deliveryTime, const PayOffBridge& payOff);

	virtual ulong MaxNumberOfCashFlows() const;
	virtual MJArray PossibleCashFlowTimes() const;
	virtual ulong CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const = 0;
	
	virtual PathDependent* clone() const = 0;
	virtual ~Asian() {}

protected:
	double m_DeliveryTime;
	PayOffBridge m_PayOff;
	ulong m_NumberOfTimes;
};

class __declspec(dllexport) AsianArithmetic : public Asian
{
public:
	AsianArithmetic(const MJArray& lookAtTimes, double deliveryTime, const PayOffBridge& payOff);

	virtual ulong CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const;
	virtual PathDependent* clone() const;
	
	virtual ~AsianArithmetic() {}
};

class __declspec(dllexport) AsianGeometric : public Asian
{
public:
	AsianGeometric(const MJArray& lookAtTimes, double deliveryTime, const PayOffBridge& payOff);

	virtual ulong CashFlows(const MJArray& spotValues, std::vector<CashFlow>& generatedCashFlows) const;
	virtual PathDependent* clone() const;

	virtual ~AsianGeometric() {}
};


