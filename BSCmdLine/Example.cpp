#include "Example.h"

#include "BSMonteCarlo/Statistics/Statistics.h"
#include "BSMonteCarlo/Statistics/ConvergenceTable.h"
#include "BSMonteCarlo/Vanilla/SimpleMC.h"
#include "BSMonteCarlo/Random/AntiThetic.h"
#include "BSMonteCarlo/Random/ParkMiller.h"

// Asian options
#include "BSMonteCarlo/Exotic/ExoticEngineBS.h"
#include "BSMonteCarlo/Exotic/PathDependentAsian.h"

#include <iostream>
#include <vector>

typedef unsigned long ulong;

void Example::displayOptionPricer() const
{
	UserDefinedPayOff userPayOff;
	
	std::cout << "Present value of option: " << userPayOff.getPayOff() << std::endl;
}

void Example::displayVanillaOptionPricer() const
{
	double expiry = 1;
	double strike = 50;
	double spot = 40;
	double vol = 0.3;
	double r = 0.05;

	double powerStrike = 90;
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
	SimpleMonteCarlo(VanillaOption(PayOffPowerCall(powerStrike, power), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statPowerCall);
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

void Example::compareRandomGenerators() const
{
	double strike = 48;
	double expiry = 2;

	double spot = 40;
	double vol = 0.3;
	double r = 0.05;
	ulong numPaths = 1.e+06;

	StatisticsMean statCallDefault;
	StatisticsMean statCallParkMiller;
	StatisticsMean statCallParkMillerAntiThetic;

	ulong dimensionality = 1;
	RandomParkMiller generatorPM(dimensionality);
	AntiThetic generatorPMATh(Wrapper<RandomParkMiller>(generatorPM));
	

	VanillaOption option(PayOffCall(strike), expiry);
	SimpleMonteCarlo(option, spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statCallDefault);
	SimpleMonteCarlo(option, spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statCallParkMiller, generatorPM);
	SimpleMonteCarlo(option, spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statCallParkMillerAntiThetic, generatorPM);
	double priceCall = calculateCallPrice(strike, expiry, spot, vol, r);

	std::cout << "Price of a call option: \n";
	std::cout << "For default random generator: " << statCallDefault.GetResultsSoFar()[0][0] << ".\n";
	std::cout << "For Park Miller random generator: " << statCallParkMiller.GetResultsSoFar()[0][0] << ".\n";
	std::cout << "For antithetic Park Miller random generator: " << statCallParkMillerAntiThetic.GetResultsSoFar()[0][0] << ".\n";
	std::cout << "Theoretical value: " << priceCall << ".\n";
}

void Example::verifyRandomness() const
{
	ulong dimensionality = 1;
	RandomParkMiller generator(1);
	MJArray variateArray(1);

	ulong numSamples = 1.e+07;
	std::vector<double> samples(numSamples);
	for (int i = 0; i < numSamples; ++i)
	{
		generator.GetUniforms(variateArray);
		samples[i] = variateArray[0];
	}
	
	StatisticsMoments statsMoments;
	statsMoments.DumpResults(samples);

	std::vector<std::vector<double>> results = statsMoments.GetResultsSoFar();

	std::cout << "The moments are: " << results[0][0] << ", " << results[0][1] << ", " << results[0][2] << ", " << results[0][3] << ".\n";
}

void Example::compareRandomGeneratorsConvergence() const
{
	ulong dimensionality = 1;

	RandomParkMiller generatorPM(dimensionality);
	AntiThetic generatorPMATh(generatorPM);

	double strike = 50;
	double expiry = 1;

	double spot = 40;
	double vol = 0.3;
	double r = 0.05;
	ulong numPaths = 1.e+07;

	StatisticsMean statCallPM;
	StatisticsMean statCallPMATh;
	Wrapper<StatisticsMC> wrapperPM(statCallPM);
	Wrapper<StatisticsMC> wrapperPMAth(statCallPMATh);

	ConvergenceTable tablePM(wrapperPM);
	ConvergenceTable tablePMATh(wrapperPMAth);		

	VanillaOption option(PayOffCall(strike), expiry);
	SimpleMonteCarlo(option, spot, ParametersConstant(vol), ParametersConstant(r), numPaths, tablePM, generatorPM);

	generatorPMATh.Reset();	// not needed as we do deep copy at the beginning
	SimpleMonteCarlo(option, spot, ParametersConstant(vol), ParametersConstant(r), numPaths, tablePMATh, generatorPMATh);

	std::cout << "Price of a call option\n";
	std::cout << "Park-Miller\tAnti-thetic Park-Miller\n";

	auto resultsPM = tablePM.GetResultsSoFar();
	auto resultsPMATh = tablePMATh.GetResultsSoFar();

	double pvCall = calculateCallPrice(strike, expiry, spot, vol, r);

	for (int i = 0; i < resultsPM.size(); ++i)
	{
		std::cout << resultsPM[i][0] - pvCall << "\t" << resultsPM[i][1] << "\t\t" << resultsPMATh[i][0] - pvCall << "\t" << resultsPMATh[i][1] << "\n";
	}
}

//void Example::displayAsianOptionPricer() const
//{
//	enum Option {Call = 1, Put, Barrier};
//	int optionType;
//	std::cout << "Declare type of Arithmetic Asian option desired:\n1 Call\t 2 Put\t 3 Barrier: ";
//	std::cin >> optionType;
//
//	double expiry = 1;
//	double strike = 50;
//	double spot = 40;
//	double vol = 0.3;
//	double rate = 0.05;
//	double dividend = 0;
//	ulong numPaths = 1.e+06;
//	ulong numDates = 1;
//	
//	std::cout << "Expiry: "
//	
//
//	PayOffCall payOffCall(strike);
//	MJArray times(numDates);
//
//	double avePeriod = expiry / numDates;
//
//	for (ulong i = 0; i < numDates; ++i)
//		times[i] = (1.0 + i) * avePeriod;
//
//	ParametersConstant volP(vol);
//	ParametersConstant rateP(rate);
//	ParametersConstant dividendP(dividend);
//
//	PathDependentAsian callOption(times, expiry, payOffCall);
//
//	StatisticsMean gatherer;
//	ConvergenceTable gathererTwo(gatherer);
//
//	RandomParkMiller generator(numDates);
//	AntiThetic generatorTwo(generator);
//
//	ExoticEngineBS engineBS(Wrapper<PathDependent>(callOption),rateP,dividendP,volP,Wrapper<RandomBase>(generator),spot);
//	engineBS.DoSimulation(gatherer, numPaths);
//
//	std::vector<std::vector<double>> results = gatherer.GetResultsSoFar();
//	std::cout << "Price of Asian call option: " << results[0][0] << std::endl;
//}