#pragma once

#include <cmath>

class Example
{
public:
	void displayVanillaOptionPricer() const;
	void displayOptionPricesConvergence() const;
	void checkMoments() const;
	void compareRandomGenerators() const;
	void compareRandomGeneratorsConvergence() const;

	// Choice of option
	void displayOptionPricer() const;

	void verifyRandomness() const;

	void displayBinomialTree() const;
private:
	inline double cumStdNormal(double x) const;
	inline double calculateCallPrice(double strike, double expiry, double spot, double vol, double r) const;
};

double Example::cumStdNormal(double x) const
{
	return 0.5 * (1 + erf(x / sqrt(2)));
}

double Example::calculateCallPrice(double strike, double expiry, double spot, double vol, double r) const
{
	double dPlus = (log(spot / strike) + (r + 0.5 * vol * vol) * expiry) / (vol * sqrt(expiry));
	double dMinus = dPlus - (vol * sqrt(expiry));

	return spot * cumStdNormal(dPlus) - strike * exp(-r * expiry) * cumStdNormal(dMinus);
}
	
