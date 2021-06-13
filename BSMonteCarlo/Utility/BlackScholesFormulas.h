#pragma once

#include <cmath>

inline constexpr double pi()
{
	return atan(1) * 4;
}

inline double stdNormal(double x)
{
	return 0.5 * (1 + erf(x / sqrt(2)));
}

inline double densityNormal(double x)
{
	return exp(-0.5 * x * x) / sqrt(2 * pi());
}

namespace BS
{
	auto dPlus = [](double spot, double strike, double expiry, double r, double d, double vol)
	{
		return (log(spot / strike) + (r - d + 0.5 * vol * vol) * expiry) / (vol * sqrt(expiry));
	};

	auto dMinus = [](double spot, double strike, double expiry, double r, double d, double vol)
	{
		return dPlus(spot, strike, expiry, r, d, vol) - vol * sqrt(expiry);
	};

	double BlackScholesCall(double spot, double strike, double r, double d, double vol, double expiry)
	{
		double dP = dPlus(spot, strike, expiry, r, d, vol);
		double dM = dMinus(spot, strike, expiry, r, d, vol);

		return spot * exp(-d * expiry) * stdNormal(dP) - strike * exp(-r * expiry) * stdNormal(dM);
	}

	double BlackScholesPut(double spot, double strike, double r, double d, double vol, double expiry)
	{
		double dP = dPlus(spot, strike, expiry, r, d, vol);
		double dM = dMinus(spot, strike, expiry, r, d, vol);

		return strike * exp(-r * expiry) * stdNormal(-dM) - spot * exp(-d * expiry) * stdNormal(-dP);
	}

	double BlackScholesDigitalCall(double spot, double strike, double r, double d, double vol, double expiry)
	{
		double dM = dMinus(spot, strike, expiry, r, d, vol);
		
		return exp(-r * expiry) * stdNormal(dM);
	}

	double BlackScholesDigitalPut(double spot, double strike, double r, double d, double vol, double expiry)
	{
		double dM = dMinus(spot, strike, expiry, r, d, vol);

		return exp(-r * expiry) * stdNormal(-dM);
	}

	double BlackScholesCallVega(double spot, double strike, double r, double d, double vol, double expiry)
	{
		double dP = dPlus(spot, strike, r, d, vol, expiry);

		return spot * exp(-d * expiry) * sqrt(expiry) * densityNormal(dP);
	}
}


