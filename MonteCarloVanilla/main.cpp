#include "Vanilla.h"
#include "SimpleMC.h"

#include <iostream>

int main()
{
	double expiry = 1;
	double strike = 50;
	double spot = 40;
	double vol = 0.3;
	double r = 0.05;
	
	double poweStrike = 90;
	double power = 1.25;
	unsigned long numPaths = pow(10,6);

	double strikes[1] = { strike };
	double* strikesDD = new double[2];
	*strikesDD = 45;
	*(strikesDD + 1) = 50;

	double pvCall = SimpleMonteCarlo2(VanillaOption(PayOffCall(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths);	// observe that you pass a PayOffCall instead of a bridge; accepted because of the constructor in the bridge
	double pvPut = SimpleMonteCarlo2(VanillaOption(PayOffPut(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths);
	double pvDD = SimpleMonteCarlo2(VanillaOption(PayOffDoubleDigital(*strikesDD,*(strikesDD+1)), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths);
	double pvPowerCall = SimpleMonteCarlo2(VanillaOption(PayOffPowerCall(poweStrike, power), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths);
	std::cout << "Our European call options costs: " << pvCall << ".\n";
	std::cout << "Our European put options costs: " <<  pvPut << ".\n";
	std::cout << "Checking put-call parity: " << pvCall + exp(-r * expiry) * strike << " has to be equal to " << pvPut + spot << ".\n";
	std::cout << "Present value of double-digital option is: " << pvDD << ".\n";
	std::cout << "Present value of a power call is " << pvPowerCall << ".\n";

	UserDefinedPayOff userPayOff;
	std::cout << "Payoff is: " << userPayOff.getPayOff() << std::endl;

	return 0;
}