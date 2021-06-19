#pragma once

class __declspec(dllexport) BSCall
{
public:
	BSCall(double r, double d, double T, double spot, double strike);
	double operator() (double vol) const;
private:
	double m_r;
	double m_d;
	double m_T;
	double m_Spot;
	double m_Strike;
};

class __declspec(dllexport) BSCall2 
{
public:
	BSCall2(double r, double d, double T, double spot, double strike);
	
	double Price(double vol) const;
	double Vega(double vol) const;
private:
	double m_r;
	double m_d;
	double m_T;
	double m_Spot;
	double m_Strike;
};
