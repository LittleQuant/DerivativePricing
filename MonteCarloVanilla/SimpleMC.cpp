#include "SimpleMC.h"

#include <cmath>
#include <random>

double SimpleMonteCarlo2(const VanillaOption& option, double spot, const Parameters& vol, const Parameters& r, ulong numPaths)
{
	// Implementation of an European Call Option
	// log(S_t) = S_0 + (r-1/2 vol^2) * expiry + vol * sqrt(t) * Normal(0,1)

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 1);

	double expiry = option.getExpiry();
	double variance = vol.IntegralSquare(0, expiry);
	double stdDev = sqrt(variance);
	double itoCorrection = -0.5 * variance;

	double movedSpot = spot * exp(r.Integral(0,expiry) + itoCorrection);
	double thisSpot = 0;
	double runningSum = 0;

	for (int i = 0; i < numPaths; i++)
	{
		double rand = distribution(generator);
		thisSpot = movedSpot * exp(stdDev * rand);
		double thisPayoff = option.optionPayOff(thisSpot);
		
		runningSum += thisPayoff;
	}

	return exp(-r.Integral(0,expiry) * expiry) * (runningSum / numPaths);
}