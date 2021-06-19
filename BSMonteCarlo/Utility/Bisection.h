#pragma once

#include <cmath>

template<typename T>
__declspec(dllexport) double Bisection(double target, double low, double high, double tol, T function)
{
	double x = 0.5 * (low + high);
	double y = function(x);

	while (abs(y - target) > tol)
	{
		if (y < target)
			low = x;
		else
			high = x;

		x = 0.5 * (low + high);

		y = function(x);
	}

	return x;
}
