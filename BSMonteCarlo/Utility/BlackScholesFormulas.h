#pragma once

#include <cmath>

inline double stdNormal(double x)
{
	return 0.5 * (1 + erf(x / sqrt(2)));
}

namespace BS
{
	auto numeratorPlus = [](double spot, double strike, double r, double d)

	double BlackScholesCall(double spot, double strike, double r, double d, double vol, double expiry)
	{
		double numeratorPlus = log(spot / strike) + (r - d + 0.5 * vol * vol) * expiry;
		double numeratorMinus = numeratorPlus - vol * vol * expiry;
		double denominator = vol * sqrt(expiry);
		double dPlus = stdNormal(numeratorPlus / denominator);
		double dMinus = stdNormal(numeratorMinus / denominator);
		
		return stdNormal(spot);
	}
}


