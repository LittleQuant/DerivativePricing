#include "BinomialTree.h"

#include <exception>

SimpleBinomialTree::SimpleBinomialTree(double spot, const Parameters& rate, const Parameters& dividend, double vol, ulong numSteps, double expiry)
	: m_Spot(spot), m_Rate(rate), m_Dividend(dividend), m_Vol(vol), m_NumSteps(numSteps), m_Expiry(expiry), m_Discounts(numSteps)
{
	m_TreeBuilt = false;
}

void SimpleBinomialTree::BuildTree()
{
	double dt = m_Expiry / m_NumSteps;
	m_Tree.resize(m_NumSteps + 1);

	double initialLogSpot = log(m_Spot);

	for (ulong i = 0; i <= m_NumSteps; ++i)
	{
		m_Tree[i].resize(i + 1);
		double thisTime = i * dt;

		double movedLogSpot = initialLogSpot + m_Rate.Integral(0, thisTime) - m_Dividend.IntegralSquare(0, thisTime) - 0.5 * m_Vol * m_Vol * thisTime;
		double sd = m_Vol * sqrt(dt);

		for (long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j += 2, k++)
		{
			m_Tree[i][k].first = exp(movedLogSpot + j * sd);
		}
	}

	for (ulong l = 0; l < m_NumSteps; l++)
	{
		m_Discounts[l] = exp(-m_Rate.Integral(l * dt, (l+1.0) * dt));
	}

	m_TreeBuilt = true;
}

double SimpleBinomialTree::GetThePrice(const TreeProduct& product)
{
	double dt = m_Expiry / m_NumSteps;

	if (!m_TreeBuilt)
		BuildTree();

	if (product.GetFinalTime() != m_Expiry)
		throw std::exception("Mismatched product in SimpleBinomialTree!");

	for (long j = -static_cast<long>(m_NumSteps), k = 0; j <= static_cast<long>(m_NumSteps); j += 2, k++)
	{
		m_Tree[m_NumSteps][k].second = product.FinalPayOff(m_Tree[m_NumSteps][k].first);
	}

	for (ulong i = 1; i <= m_NumSteps; i++)
	{
		ulong index = m_NumSteps - i;
		double thisTime = index * dt;

		for (long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j += 2, k++)
		{
			double spot = m_Tree[index][k].first;
			double futureDiscountedValue = 0.5 * m_Discounts[index] * (m_Tree[index + 1][k].second + m_Tree[index + 1][k + 1].second);
			m_Tree[index][k].second = product.PreFinalPayOff(spot, thisTime, futureDiscountedValue);
		}
	}

	return m_Tree[0][0].second;
}