#include "pch.h"

#include "SimpleMC.h"

#include <cmath>
#include <random>

void SimpleMonteCarlo(const VanillaOption& option, double spot, const Parameters& vol, const Parameters& r, ulong numPaths, StatisticsMC& gatherer)
{
	// Implementation of an European Call Option
	// log(S_t) = S_0 + (r - 0.5 * vol^2) * t + vol * sqrt(t) * Normal(0,1)

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 1);

	double expiry = option.getExpiry();
	double variance = vol.IntegralSquare(0, expiry);
	double stdDev = sqrt(variance);
	double itoCorrection = -0.5 * variance;

	double movedSpot = spot * exp(r.Integral(0,expiry) + itoCorrection);
	double thisSpot = 0;
	double discounting = exp(-r.Integral(0, expiry));

	for (int i = 0; i < numPaths; i++)
	{
		double rand = distribution(generator);
		thisSpot = movedSpot * exp(stdDev * rand);
		double thisPayoff = option.optionPayOff(thisSpot);
		
		gatherer.DumpOneResult(discounting * thisPayoff);
	}
}

void SimpleMonteCarlo(const VanillaOption& option, double spot, const Parameters& vol, const Parameters& r, ulong numPaths, StatisticsMC& gatherer, RandomBase& generator)
{
	generator.ResetDimensionality(1);

	double expiry = option.getExpiry();
	double variance = vol.IntegralSquare(0, expiry);
	double stdDev = sqrt(variance);
	double itoCorrection = - 0.5 * variance;

	double movedSpot = spot * exp(r.Integral(0, expiry) + itoCorrection);
	double thisSpot = 0;
	double discounting = exp(-r.IntegralSquare(0, expiry));

	MJArray variateArray(1);

	for (ulong i = 0; i < numPaths; ++i)
	{
		generator.GetGaussians(variateArray);
		thisSpot = movedSpot * exp(stdDev * variateArray[0]);
		double thisPayOff = option.optionPayOff(thisSpot);
		gatherer.DumpOneResult(discounting * thisPayOff);
	}
}