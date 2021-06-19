#pragma once

#include <cmath>

template<typename T, double (T::*Value)(double) const, double (T::*Derivative)(double) const>
__declspec(dllexport) double NewtonRaphson(double target, double start, double tol, const T& object)
{
	double x = start;
	double y = (object.*Value)(x) - target;
	
	while (abs(y) > tol)
	{
		x = x - y / (object.*Derivative)(x);
		y = (object.*Value)(x) - target;
	}

	return x;
}
