#pragma once

#include "../Utility/Arrays.h"
#include "../Utility/Parameters.h"
#include "TreeProduct.h"

#include <vector>

typedef unsigned long ulong;

class __declspec(dllexport) SimpleBinomialTree
{
public:
	SimpleBinomialTree(double spot, const Parameters& rate, const Parameters& dividend, double vol, ulong numSteps, double expiry);
	double GetThePrice(const TreeProduct& tree);

protected:
	void BuildTree();

private:
	double m_Spot;
	Parameters m_Rate;
	Parameters m_Dividend;
	double m_Vol;
	ulong m_NumSteps;
	double m_Expiry;
	bool m_TreeBuilt;
		
	std::vector<std::vector<std::pair<double, double>>> m_Tree;
	MJArray m_Discounts;
};
