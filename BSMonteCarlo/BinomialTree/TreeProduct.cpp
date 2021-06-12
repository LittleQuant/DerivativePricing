#include "TreeProduct.h"

TreeProduct::TreeProduct(double finalTime) : m_FinalTime(finalTime) {}

double TreeProduct::GetFinalTime() const
{
	return m_FinalTime;
}