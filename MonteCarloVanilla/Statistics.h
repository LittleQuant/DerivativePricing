#pragma once

#include <vector>
#include <iostream>

// Interface
class __declspec(dllexport) StatisticsMC
{
public:
	StatisticsMC();
	virtual void DumpOneResult(double result) = 0;
	virtual StatisticsMC* clone() const = 0;
	virtual ~StatisticsMC();
	virtual std::vector<std::vector<double>> GetResultsSoFar() const = 0;
private:
};

class StatisticsMean : public StatisticsMC
{
public:
	StatisticsMean() {}
	virtual void DumpOneResult(double result);
	virtual StatisticsMC* clone() const;
	virtual ~StatisticsMean() {}

	virtual std::vector<std::vector<double>> GetResultsSoFar() const;
private:
	double m_RunningSum = 0;
	unsigned long m_PathsDone = 0;
};

class __declspec(dllexport)StatisticsMoments : public StatisticsMC
{
public:
	StatisticsMoments();
	virtual void DumpOneResult(double result);
	virtual void DumpResults(std::vector<double> results);
	virtual StatisticsMC* clone() const;
	virtual std::vector<std::vector<double>> GetResultsSoFar() const;
	virtual ~StatisticsMoments() {}
private:
	std::vector<double> m_Samples{};
};