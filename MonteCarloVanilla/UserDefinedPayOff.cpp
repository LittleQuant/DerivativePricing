#include "pch.h"

#include "SimpleMC.h"
#include "Vanilla.h"

#include <algorithm>
#include <cmath>
#include <iostream>

enum {EuropeanCall = 1, EuropeanPut, DoubleDigital, PowerCall, PowerPut};

UserDefinedPayOff::UserDefinedPayOff()
{
	double strike, expiry, spot, vol, r, power;
		
	std::cout << "Expiry: ";	std::cin >> expiry;
	std::cout << "Spot: ";		std::cin >> spot;
	std::cout << "Vol: ";		std::cin >> vol;
	std::cout << "Rate: ";		std::cin >> r;
	std::cout << "Log-Number of MC paths: "; std::cin >> power;
	unsigned long numPaths = pow(10,power);

	int optionType;
	std::cout << "Choose from one of the below: \n";
	std::cout << "1 EuropeanCall, 2 European Put, 3 DoubleDigital, 4 PowerCall, 5 PowerPut.\n";

	std::cout << "Type of option (enter number): ";
	std::cin >> optionType;

	std::cout << "Enter strike: ";		std::cin >> strike;

	PayOff* thisPayOff;

	switch (optionType)
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
	SimpleMonteCarlo(VanillaOption(*thisPayOff, expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, gatherer);

	m_PayOff = gatherer.GetResultsSoFar()[0][0];

	delete thisPayOff;
}

double UserDefinedPayOff::getPayOff() const { return m_PayOff; }