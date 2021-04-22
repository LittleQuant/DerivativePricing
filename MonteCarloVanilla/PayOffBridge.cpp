// Employing the bridge pattern for our PayOff class

#include "PayOffBridge.h"

PayOffBridge::PayOffBridge(const PayOffBridge& original)
{
	m_PayOff = original.m_PayOff->clone();
}

PayOffBridge::PayOffBridge(const PayOff& innerPayOff)
{
	m_PayOff = innerPayOff.clone();
}

PayOffBridge& PayOffBridge::operator= (const PayOffBridge& original)
{
	if (this != &original)
	{
		delete m_PayOff;
		m_PayOff = original.m_PayOff->clone();
	}

	return *this;
}

PayOffBridge::~PayOffBridge()
{
	delete m_PayOff;
}

double PayOffBridge::operator()(double spot) const
{
	return (*m_PayOff)(spot);
}