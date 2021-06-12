#pragma once

#include "TreeProduct.h"
#include "../PayOff/PayOffBridge.h"

class __declspec(dllexport) TreeEuropean : public TreeProduct
{
public:
	TreeEuropean(double finalTime, const PayOffBridge& pyOff);
	virtual double FinalPayOff(double spot) const;
	virtual double PreFinalPayOff(double spot, double time, double discountedFutureValue) const;

	virtual TreeProduct* clone() const;
	virtual ~TreeEuropean() {}
private:
	PayOffBridge m_PayOff;
};
