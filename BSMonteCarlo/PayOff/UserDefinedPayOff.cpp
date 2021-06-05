#include "pch.h"

#include "../Exotic/ExoticEngineBS.h"
#include "../Exotic/Asian.h"
#include "../Exotic/Barrier.h"
#include "../Random/ParkMiller.h"
#include "../Vanilla/SimpleMC.h"
#include "../Vanilla/Vanilla.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>

enum {EuropeanCall = 1, EuropeanPut, DoubleDigital, PowerCall, PowerPut};
enum {AritAsianCall = 1, AritAsianPut, GeomAsianCall, GeomAsianPut, KnockOutUpCall, KnockOutUpPut};

// We assume beforehand the values
void setParameters(std::map<std::string, double>& params)
{
	std::cout << "Expiry: ";	std::cin >> params["Expiry"];
	std::cout << "Spot: ";		std::cin >> params["Spot"];
	std::cout << "Vol: ";		std::cin >> params["Vol"];
	std::cout << "Rate: ";		std::cin >> params["Rate"];
	std::cout << "Dividend: ";	std::cin >> params["Dividend"];
	std::cout << "Log-Number of MC paths: "; std::cin >> params["PowerPaths"];
}

UserDefinedPayOff::UserDefinedPayOff()
{
	std::map<std::string, double> params;
	
	double strike;

	int optionType;
	int optionSubType;
	std::cout << "Choose from one of the below: \n";
	std::cout << "1 Vanilla, 2 Exotic.\n";
	std::cout << "Type of option (enter number): ";
	std::cin >> optionType;

	if (optionType == 1)
	{
		std::cout << "Choose subtype: ";
		std::cout << "1 European Call, 2 European Put, 3 DoubleDigital, 4 PowerCall, 5 PowerPut. \n";

		std::cout << "Subtype of vanilla option (enter number): ";
		std::cin >> optionSubType;
		
		setParameters(params);

		std::cout << "Enter strike: ";		std::cin >> strike;

		PayOff* thisPayOff;

		switch (optionSubType)
		{
		case EuropeanCall:
			thisPayOff = new PayOffCall(strike);
			break;
		case EuropeanPut:
			thisPayOff = new PayOffPut(strike);
			break;
		case DoubleDigital:
			double secondStrike;
			std::cout << "Enter second strike: ";	std::cin >> secondStrike;
			thisPayOff = new PayOffDoubleDigital((std::min)(strike, secondStrike), (std::max)(strike, secondStrike));
			break;
		case PowerCall:
			double powerOfCall;
			std::cout << "Enter power for call: ";	std::cin >> powerOfCall;
			thisPayOff = new PayOffPowerCall(strike, powerOfCall);
			break;
		case PowerPut:
			double powerOfPut;
			std::cout << "Enter power for put: ";	std::cin >> powerOfPut;
			thisPayOff = new PayOffPowerCall(strike, powerOfPut);
			break;
		default:
			throw("Wrong type, we throw error");
		}

		StatisticsMean gatherer;
		SimpleMonteCarlo(VanillaOption(*thisPayOff, params["Expiry"]), params["Spot"], ParametersConstant(params["Vol"]), ParametersConstant(params["Rate"]), pow(10,params["PowerPaths"]), gatherer);

		m_PayOff = gatherer.GetResultsSoFar()[0][0];

		delete thisPayOff;
	}
	else
	{
		std::cout << "Choose subtype: ";
		std::cout << "1 Arithmetic Asian Call,2 Arithmetic Asian Put, 3 Geometric Asian Call, 4 Geometric Asian Put,\n";
		std::cout << "5 Knock Out Up Call, 6 Knock Out Up Put.\n";
		std::cout << "Subtype of exotic option (enter number): ";
		std::cin >> optionSubType;

		setParameters(params);

		ulong numDates;
		
		std::cout << "Enter strike: "; std::cin >> strike;
		std::cout << "Enter number of look-up points: "; std::cin >> numDates;

		MJArray times(numDates);
		double avePeriod = params["Expiry"] / numDates;
		for (ulong i = 0; i < times.size(); i++)
		{
			times[i] = (1.0 + i) * avePeriod;
		}

		PayOffBridge payOff(PayOffCall(0));	// empty payoff to change in the switch statement

		PathDependent* optionPtr;

		switch (optionSubType)
		{
		case AritAsianCall:			// puting braces to avoid error transfer of control bypasses initialization
		{
			PayOffCall payOffCall(strike);
			payOff = payOffCall; 
			optionPtr = new AsianArithmetic(times, params["Expiry"], payOff);
		}
		
			break;
		case AritAsianPut:
		{
			PayOffPut payOffPut(strike);
			payOff = payOffPut;
			optionPtr = new AsianArithmetic(times, params["Expiry"], payOff);
		}
			break;

		case GeomAsianCall:
		{
			PayOffCall payOffCall(strike);
			payOff = payOffCall;
			optionPtr = new AsianGeometric(times, params["Expiry"], payOff);
		}
		break;

		case GeomAsianPut:
		{
			PayOffPut payOffPut(strike);
			payOff = payOffPut;
			optionPtr = new AsianGeometric(times, params["Expiry"], payOff);
		}
		break;

		case KnockOutUpCall:
		{
			double barrier;
			double rebate;
			std::cout << "Enter barrier: "; std::cin >> barrier;
			std::cout << "Enter rebate: "; std::cin >> rebate;
			PayOffCall payOffCall(strike);
			payOff = payOffCall;
			optionPtr = new Barrier(times, params["Expiry"], barrier, true, true, payOff, rebate);
		}
		break;

		case KnockOutUpPut:
		{
			double barrier;
			double rebate;
			std::cout << "Enter barrier: "; std::cin >> barrier;
			std::cout << "Enter rebate: "; std::cin >> rebate;
			PayOffPut payOffPut(strike);
			payOff = payOffPut;
			optionPtr = new Barrier(times, params["Expiry"], barrier, true, true, payOff, rebate);
		}
		break;

		default:
			throw new std::exception("Wrong type of option!\n");
		}

		
		StatisticsMean gatherer;
		RandomParkMiller generator(numDates);
		ExoticEngineBS engine(Wrapper<PathDependent>(*optionPtr), ParametersConstant(params["Rate"]), ParametersConstant(params["Dividend"]), ParametersConstant(params["Vol"]), Wrapper<RandomBase>(generator), params["Spot"]);
		engine.DoSimulation(gatherer, pow(10, params["PowerPaths"]));
		
		m_PayOff = gatherer.GetResultsSoFar()[0][0];

		delete optionPtr;
	}
}

double UserDefinedPayOff::getPayOff() const { return m_PayOff; }