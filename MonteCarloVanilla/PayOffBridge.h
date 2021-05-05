#pragma once

// Employing the bridge pattern for our PayOff class

#include "PayOff.h"

class __declspec(dllexport) PayOffBridge
{
public:
	PayOffBridge(const PayOffBridge& original);
	PayOffBridge(const PayOff& innerPayOff);
	
	double operator() (double spot) const;
	PayOffBridge& operator= (const PayOffBridge& original);
	~PayOffBridge();
private:
	PayOff* m_PayOff;
};
