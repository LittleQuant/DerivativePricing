#include "ExoticEngineBS.h"

ExoticEngineBS::ExoticEngineBS(const Wrapper<PathDependent>& product, const Parameters& rates, const Parameters& dividends, const Parameters& vol, const Wrapper<RandomBase>& generator, double spot)
	: ExoticEngine(product, rates), m_Generator(generator)
{
	MJArray times(product->GetLookAtTimes());
	m_NumOfTimes = times.size();
	
	m_Generator->ResetDimensionality(m_NumOfTimes);
	m_Drifts.resize(m_NumOfTimes);
	m_StandardDeviations.resize(m_NumOfTimes);

	double variance = vol.IntegralSquare(0.0, times[0]);
	m_Drifts[0] = rates.Integral(0.0, times[0]) - dividends.Integral(0.0, times[0]) - 0.5 * variance;
	m_StandardDeviations[0] = sqrt(variance);

	for (ulong i = 1; i < m_NumOfTimes; ++i)
	{
		double thisVariance = vol.IntegralSquare(times[i-1], times[i]);
		m_Drifts[i] = rates.Integral(times[i - 1], times[i]) - dividends.Integral(times[i - 1], times[i]) - 0.5 * thisVariance;
		m_StandardDeviations[i] = sqrt(thisVariance);
	}

	m_LogSpot = log(spot);
	m_Variates.resize(m_NumOfTimes);
}

void ExoticEngineBS::GetOnePath(MJArray& spotValues)
{
	m_Generator->GetGaussians(m_Variates);
	double currentLogSpot = m_LogSpot;

	for (ulong i = 0; i < m_NumOfTimes; i++)
	{
		currentLogSpot += m_Drifts[i];
		currentLogSpot += m_StandardDeviations[i]*m_Variates[i];
		spotValues[i] = exp(currentLogSpot);
	}
}