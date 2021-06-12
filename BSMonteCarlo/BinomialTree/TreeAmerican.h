#pragma once

#include "TreeProduct.h"
#include "../PayOff/PayOffBridge.h"

class __declspec(dllexport) TreeAmerican : public TreeProduct
{
public:
	TreeAmerican(double finalTime, const PayOffBridge& payOff);
	virtual double FinalPayOff(double spot) const;
	virtual double PreFinalPayOff(double spot, double time, double discountedFutureValue) const;

	virtual TreeProduct* clone() const;
	virtual ~TreeAmerican() {}
private:
	PayOffBridge m_PayOff;
};

