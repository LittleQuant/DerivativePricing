#pragma once

// Implementing a Vanilla Option class using --the bridge pattern--

#include "../PayOff/PayOffBridge.h"

class __declspec(dllexport) VanillaOption
{
public:
	VanillaOption(const PayOffBridge& payOff, double expiry);
	double getExpiry() const;
	double optionPayOff(double spot) const;
private:
	double m_Expiry;
	PayOffBridge m_PayOff;
};