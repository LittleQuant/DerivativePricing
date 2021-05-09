#define BOOST_TEST_MODULE VanillaOptions

#include "boost/test/unit_test.hpp"
#include "MonteCarloVanilla/SimpleMC.h"
#include "MonteCarloVanilla/Statistics.h"

#include <cmath>
#include <iostream>
#include <random>
#include <utility>

namespace utf = boost::unit_test;

typedef unsigned long ulong;

inline double stdNormal(double x)
{
    return 0.5 * (1 + erf(x / sqrt(2)));
}

class TestData
{
public:
    TestData(double spot, double expiry, double strike, double vol, double rate, ulong numPaths) : m_Spot(spot), m_Expiry(expiry), m_Strike(strike), m_Vol(vol), m_Rate(rate), m_NumPaths(numPaths)  {}
    std::pair<double,double> pvECallPut() const
    {
        double dplus = (log(m_Spot / m_Strike) + (m_Rate + 0.5 * m_Vol * m_Vol) * m_Expiry) / (m_Vol * sqrt(m_Expiry));
        double dminus = dplus - (m_Vol * sqrt(m_Expiry));

        double call = m_Spot * stdNormal(dplus) - m_Strike * exp(-m_Rate * m_Expiry) * stdNormal(dminus);
        double put = m_Strike * exp(-m_Rate * m_Expiry) * stdNormal(-dminus) - m_Spot * stdNormal(-dplus);
        
        return std::make_pair(call, put);
    }

private:
    double m_Spot = 0;
    double m_Expiry = 0;
    double m_Strike = 0;
    double m_Vol = 0;
    double m_Rate = 0;
    unsigned long m_NumPaths = 0;
};

BOOST_AUTO_TEST_CASE(European1)
{
    double expiry = 1;
    double strike = 50;
    double spot = 40;
    double vol = 0.3;
    double r = 0.05;
    unsigned long numPaths = 1.e+06;

    TestData data(spot, expiry, strike, vol, r, numPaths);
    StatisticsMean statsCall;
    StatisticsMean statsPut;
    
    std::pair<double, double> results = data.pvECallPut();
    double pvTheoreticalCall = results.first;
    double pvTheoreticalPut = results.second;
    SimpleMonteCarlo(VanillaOption(PayOffCall(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statsCall);
    SimpleMonteCarlo(VanillaOption(PayOffPut(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statsPut);
    double pvMCCall = statsCall.GetResultsSoFar()[0][0];
    double pvMCPut = statsPut.GetResultsSoFar()[0][0];

    BOOST_CHECK_MESSAGE(abs(pvTheoreticalCall - pvMCCall) < 0.01, "Error in call\nTheoretical: " << pvTheoreticalCall << "Monte Carlo: " << pvMCCall << "\n");
    BOOST_CHECK_MESSAGE(abs(pvTheoreticalPut - pvMCPut) < 0.01, "Error in put\nTheoretical: " << pvTheoreticalPut << "Monte Carlo: " << pvMCPut << "\n");

    // Checking put-call parity
    double lhs = pvMCCall + exp(-r * expiry) * strike;
    double rhs = pvMCPut + spot;
    BOOST_CHECK_MESSAGE(abs(lhs - rhs) < 0.01, "Put-call parity failed. Call side: " << lhs << " and put side " << rhs << "\n");
}

BOOST_AUTO_TEST_CASE(European2)
{
    double expiry = 1;
    double strike = 35;
    double spot = 30;
    double vol = 0.2;
    double r = 0.06;
    unsigned long numPaths = 1.e+06;

    TestData data(spot, expiry, strike, vol, r, numPaths);
    StatisticsMean statsCall;
    StatisticsMean statsPut;

    std::pair<double, double> results = data.pvECallPut();
    double pvTheoreticalCall = results.first;
    double pvTheoreticalPut = results.second;
    SimpleMonteCarlo(VanillaOption(PayOffCall(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statsCall);
    SimpleMonteCarlo(VanillaOption(PayOffPut(strike), expiry), spot, ParametersConstant(vol), ParametersConstant(r), numPaths, statsPut);
    double pvMCCall = statsCall.GetResultsSoFar()[0][0];
    double pvMCPut = statsPut.GetResultsSoFar()[0][0];

    BOOST_CHECK_MESSAGE(abs(pvTheoreticalCall - pvMCCall) < 0.01, "Error in call\nTheoretical: " << pvTheoreticalCall << "Monte Carlo: " << pvMCCall << "\n");
    BOOST_CHECK_MESSAGE(abs(pvTheoreticalPut - pvMCPut) < 0.01, "Error in put\nTheoretical: " << pvTheoreticalPut << "Monte Carlo: " << pvMCPut << "\n");

    // Checking put-call parity
    double lhs = pvMCCall + exp(-r * expiry) * strike;
    double rhs = pvMCPut + spot;
    BOOST_CHECK_MESSAGE(abs(lhs - rhs) < 0.01, "Put-call parity failed. Call side: " << lhs << " and put side " << rhs << "\n");
}

BOOST_AUTO_TEST_CASE(ValueAtRisk)
{
    int sizeSamples1 = 100;
    ulong sizeSamples2 = 1.e+06;

    std::vector<double> samples1(sizeSamples1);
    std::vector<double> samples2(sizeSamples2);

    for (int i = 0; i < sizeSamples1; ++i)
    {
        samples1[i] = (double) i + 1;
    }

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, 1);

    for (auto it = samples2.begin(); it != samples2.end(); ++it)
    {
        *it = distribution(generator);
    }

    StatisticsVaR var1;
    StatisticsVaR var2;

    var1.DumpResults(samples1);
    var2.DumpResults(samples2);

    std::vector<double> var1Results = var1.GetResultsSoFar()[0];
    std::vector<double> var2Results = var2.GetResultsSoFar()[0];
    
    BOOST_CHECK(var1Results[0] - 5 == 0);
    BOOST_CHECK(var1Results[1] - 1 == 0);
    BOOST_CHECK(abs(stdNormal(var2Results[0]) - 0.05) < 0.001);
    BOOST_CHECK(abs(stdNormal(var2Results[1]) - 0.01) < 0.001);
}


