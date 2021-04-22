#pragma once

class PayOff
{
public:
	PayOff() {}
	virtual double operator()(double spot) const = 0;
	virtual PayOff* clone() const = 0;
	virtual ~PayOff() {}
};

class UserDefinedPayOff
{
public:
	UserDefinedPayOff();
	double getPayOff() const;
private:
	double m_PayOff;
};


// Vanilla Options
class PayOffCall : public PayOff
{
public:
	PayOffCall(double strike);
	virtual double operator()(double spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffCall() {}
private:
	double m_Strike;
};

class PayOffPut : public PayOff
{
public:
	PayOffPut(double strike);
	virtual double operator()(double spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffPut() {}

private:
	double m_Strike;
};

class PayOffDoubleDigital : public PayOff
{
public:
	PayOffDoubleDigital(double lowerStrike, double doubleUpperStrike);
	virtual double operator()(double spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffDoubleDigital() {}
private:
	double m_LowerStrike;
	double m_UpperStrike;
};


// Power
class PayOffPowerCall : public PayOff
{
public:
	PayOffPowerCall(double strike, double power);
	virtual double operator()(double spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffPowerCall() {}
private:
	double m_Strike;
	double m_Power;
};

class PayOffPowerPut : public PayOff
{
public:
	PayOffPowerPut(double strike, double power);
	virtual double operator()(double spot) const;
	virtual PayOff* clone() const;
	virtual ~PayOffPowerPut() {}
private:
	double m_Strike;
	double m_Power;
};
