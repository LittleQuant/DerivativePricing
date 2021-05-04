#include "pch.h"

#include "Statistics.h"

#include <algorithm>

StatisticsMC::StatisticsMC() {};
StatisticsMC::~StatisticsMC() {};

StatisticsMC* StatisticsMean::clone() const
{
	return new StatisticsMean(*this);
}

void StatisticsMean::DumpOneResult(double result)
{
	m_PathsDone++;
	m_RunningSum += result;	
}

std::vector<std::vector<double>> StatisticsMean::GetResultsSoFar() const
{
	std::vector<std::vector<double>> results(1);
	results[0].resize(1);

	results[0][0] = m_RunningSum / m_PathsDone;

	return results;
}



StatisticsMoments::StatisticsMoments()
{
	m_Samples.reserve(1024);
}

void StatisticsMoments::DumpOneResult(double result)
{
	m_Samples.push_back(result);
}

void StatisticsMoments::DumpResults(std::vector<double> results)
{
	m_Samples.insert(m_Samples.end(), results.begin(), results.end());
}

StatisticsMC* StatisticsMoments::clone() const
{
	return new StatisticsMoments(*this);
}

std::vector<std::vector<double>> StatisticsMoments::GetResultsSoFar() const
{
	std::vector<double> answer;
	answer.reserve(4);

	// Calculating the mean
	double sum = 0;
	unsigned long numSamples = m_Samples.size();
	std::for_each(m_Samples.begin(), m_Samples.end(), [&sum](double sample) {sum += sample; });
	double mean = sum / numSamples;

	// Calculating the variance
	sum = 0;	// we now compute the sum in variance formula
	std::for_each(m_Samples.begin(), m_Samples.end(), [&sum, &mean](double sample) {sum += pow((sample - mean),2); });
	double variance = sum / numSamples;		// we expect many samples

	// Calculating skewness
	sum = 0;
	std::for_each(m_Samples.begin(), m_Samples.end(), [&sum, &mean](double sample) {sum += pow((sample - mean), 3); });
	double skewness = (sum / numSamples) / (pow(variance,1.5));

	// Calculating kurtosis
	sum = 0;
	std::for_each(m_Samples.begin(), m_Samples.end(), [&sum, &mean](double sample) {sum += pow((sample - mean), 4); });
	double kurtosis = (sum / numSamples) / (pow(variance, 2));

	answer.push_back(mean);
	answer.push_back(variance);
	answer.push_back(skewness);
	answer.push_back(kurtosis);

	return std::vector<std::vector<double>>{answer};
}

void printStatement()
{
	std::cout << "Hey" << std::endl;
}









