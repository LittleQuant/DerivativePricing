#pragma once

// Paramaters class for MC pricer designed using --the bridge pattern--

class __declspec(dllexport) ParametersInner
{
public:
	ParametersInner() {}
	virtual ParametersInner* clone() const = 0;
	virtual double Integral(double time1, double time2) const = 0;
	virtual double IntegralSquare(double time1, double time2) const = 0;

	virtual ~ParametersInner() {}
private:
};

// Wrapper class
class __declspec(dllexport) Parameters
{
public:
	Parameters(const ParametersInner& parameters);
	Parameters(const Parameters& original);
	Parameters& operator= (const Parameters& original);
	virtual ~Parameters();
	
	// Using inline as methods are one command
	inline double Integral(double time1, double time2) const;
	inline double IntegralSquare(double time1, double time2) const;

	double Mean(double time1, double time2) const;
	double RootMeanSquare(double time1, double time2) const;
private:
	ParametersInner* m_Parameters;
};

inline double Parameters::Integral(double time1, double time2) const
{
	return m_Parameters->Integral(time1, time2);
}

inline double Parameters::IntegralSquare(double time1, double time2) const
{
	return m_Parameters->IntegralSquare(time1, time2);
}

class __declspec(dllexport) ParametersConstant : public ParametersInner
{
public:
	ParametersConstant(double constant);
	virtual ParametersInner* clone() const;

	virtual double Integral(double time1, double time2) const;
	virtual double IntegralSquare(double time1, double time2) const;
private:
	double m_Constant;
	double m_ConstantSquare;
};

