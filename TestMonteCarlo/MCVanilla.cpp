#define BOOST_TEST_MODULE VanillaOptions

#include "boost/test/unit_test.hpp"
#include "MonteCarloVanilla/SimpleMC.h"

#include <cmath>
#include <iostream>

typedef unsigned long ulong;

inline double stdNormal(double x)
{
    return 0.5 * (1 + erf(x / sqrt(2)));
}

class TestData
{
public:
    TestData(double spot, double expiry, double strike, double vol, double rate, ulong numPaths) : m_Spot(spot), m_Expiry(expiry), m_Strike(strike), m_Vol(vol), m_Rate(rate), m_NumPaths(numPaths)  {}
    double pvEuropeanCall() const
    {
        double dplus = (log(m_Spot / m_Strike) + (m_Rate + 0.5 * m_Vol * m_Vol) * m_Expiry) / (m_Vol * sqrt(m_Expiry));
        double dminus = dplus - (m_Vol * sqrt(m_Expiry));

        return m_Spot * stdNormal(dplus) - m_Strike * exp(-m_Rate * m_Expiry) * stdNormal(dminus);
    }

private:
    double m_Spot = 0;
    double m_Expiry = 0;
    double m_Strike = 0;
    double m_Vol = 0;
    double m_Rate = 0;
    unsigned long m_NumPaths = 0;
};

BOOST_AUTO_TEST_CASE(EuropeanCall1)
{
    double expiry = 1;
    double strike = 50;
    double spot = 40;
    double vol = 0.3;
    double r = 0.05;
    unsigned long numPaths = 1.e+06;

    TestData data(spot, expiry, strike, vol, r, numPaths);
    StatisticsMean statCall;

    double pvTheoretical = data.pvEuropeanCall();
    SimpleMonteCarlo(VanillaOption(PayOffCall(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statCall);
    double pvMC = statCall.GetResultsSoFar()[0][0];

    BOOST_CHECK_MESSAGE(abs(pvTheoretical - pvMC) < 0.01, "Theoretical: " << pvTheoretical << "Monte Carlo: " << pvMC << "\n");
}

BOOST_AUTO_TEST_CASE(EuropeanCall2)
{
    double expiry = 1;
    double strike = 35;
    double spot = 30;
    double vol = 0.2;
    double r = 0.06;
    unsigned long numPaths = 1.e+06;

    TestData data(spot, expiry, strike, vol, r, numPaths);
    StatisticsMean statCall;

    double pvTheoretical = data.pvEuropeanCall();
    SimpleMonteCarlo(VanillaOption(PayOffCall(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statCall);
    double pvMC = statCall.GetResultsSoFar()[0][0];

    BOOST_CHECK_MESSAGE(abs(pvTheoretical - pvMC) < 0.01, "\nTheoretical: " << pvTheoretical << "\nMonte Carlo: " << pvMC << "\n");
}

BOOST_AUTO_TEST_CASE(EuropeanCall3)
{
    BOOST_CHECK(2 == 2);
}

