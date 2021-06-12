#pragma once

class __declspec(dllexport) TreeProduct
{
public:
	TreeProduct(double finalTime);
	virtual double FinalPayOff(double spot) const = 0;
	virtual double PreFinalPayOff(double spot, double time, double discountedFutureValue) const = 0;
	double GetFinalTime() const;

	virtual ~TreeProduct() {}
	virtual TreeProduct* clone() const = 0;
	
private:
	double m_FinalTime;
};
