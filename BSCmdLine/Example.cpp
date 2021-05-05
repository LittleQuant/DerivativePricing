#include "Example.h"

#include "MonteCarloVanilla/Statistics.h"
#include "MonteCarloVanilla/ConvergenceTable.h"
#include "MonteCarloVanilla/SimpleMC.h"

#include <iostream>
#include <vector>

typedef unsigned long ulong;

void Example::displayOptionPricer() const
{
	double expiry = 1;
	double strike = 50;
	double spot = 40;
	double vol = 0.3;
	double r = 0.05;

	double poweStrike = 90;
	double power = 1.25;
	unsigned long numPaths = pow(10, 6);

	double strikes[1] = { strike };
	double* strikesDD = new double[2];
	*strikesDD = 45;
	*(strikesDD + 1) = 50;

	StatisticsMean statCall;
	StatisticsMean statPut;
	StatisticsMean statDD;
	StatisticsMean statPowerCall;


	SimpleMonteCarlo(VanillaOption(PayOffCall(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statCall);	// observe that you pass a PayOffCall instead of a bridge; accepted because of the constructor in the bridge
	SimpleMonteCarlo(VanillaOption(PayOffPut(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statPut);
	SimpleMonteCarlo(VanillaOption(PayOffDoubleDigital(*strikesDD, *(strikesDD + 1)), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statDD);
	SimpleMonteCarlo(VanillaOption(PayOffPowerCall(poweStrike, power), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statPowerCall);
	std::cout << "Our European call options costs: " << statCall.GetResultsSoFar()[0][0] << ".\n";
	std::cout << "Our European put options costs: " << statPut.GetResultsSoFar()[0][0] << ".\n";
	std::cout << "Checking put-call parity: " << statCall.GetResultsSoFar()[0][0] + exp(-r * expiry) * strike << " has to be equal to " << statPut.GetResultsSoFar()[0][0] + spot << ".\n";
	std::cout << "Present value of double-digital option is: " << statDD.GetResultsSoFar()[0][0] << ".\n";
	std::cout << "Present value of a power call is " << statPowerCall.GetResultsSoFar()[0][0] << ".\n";

	UserDefinedPayOff userPayOff;
	std::cout << "Payoff is: " << userPayOff.getPayOff() << std::endl;
}

void Example::displayOptionPricesConvergence() const
{
	// Call propertiess
	double strike = 50;
	double expiry = 1;

	double spot = 40;
	double vol = 0.3;
	double r = 0.05;

	ulong numPaths = 1.0e+6;
	StatisticsMean statCall;
	Wrapper<StatisticsMC> wrapper(statCall);
	ConvergenceTable gatherer(wrapper);

	SimpleMonteCarlo(VanillaOption(PayOffCall(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r),numPaths, gatherer);

	std::vector<std::vector<double>> results = gatherer.GetResultsSoFar();

	for (int i = 0; i < results.size(); ++i)
	{
		for (int j = 0; j < results[i].size(); ++j)
		{
			std::cout << results[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void Example::checkMoments() const
{
	std::vector<double> samples{ 318,304,317,305,309,307,316,309,315,327 };
	StatisticsMoments gatherer;
	gatherer.DumpResults(samples);

	std::vector<std::vector<double>> results = gatherer.GetResultsSoFar();

	for (int i = 0; i < results[0].size(); ++i)
	{
		std::cout << results[0][i] << std::endl;
	}
}

