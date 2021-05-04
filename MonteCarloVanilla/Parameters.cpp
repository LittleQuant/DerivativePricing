#include "pch.h"

#include "Parameters.h"

Parameters::Parameters(const ParametersInner& parameters)
{
	m_Parameters = parameters.clone();
}

Parameters::Parameters(const Parameters& original)
{
	m_Parameters = original.m_Parameters->clone();
}

Parameters& Parameters::operator= (const Parameters& original)
{
	if (this != &original)
	{
		delete m_Parameters;
		m_Parameters = original.m_Parameters->clone();
	}

	return *this;
}

Parameters::~Parameters()
{
	delete m_Parameters;
}

double Parameters::Mean(double time1, double time2) const
{
	return Integral(time1, time2) / (time2 - time1);
}

double Parameters::RootMeanSquare(double time1, double time2) const
{
	return IntegralSquare(time1, time2) / (time2 - time1);
}


// ParametersConstant

ParametersConstant::ParametersConstant(double constant) : m_Constant(constant), m_ConstantSquare(constant* constant) {}

ParametersInner* ParametersConstant::clone() const
{
	return new ParametersConstant(*this);
}

double ParametersConstant::Integral(double time1, double time2) const
{
	return m_Constant * (time2 - time1);
}

double ParametersConstant::IntegralSquare(double time1, double time2) const
{
	return m_ConstantSquare * (time2 - time1);
}