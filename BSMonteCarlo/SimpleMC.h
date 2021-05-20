#pragma once

typedef unsigned long ulong;

#include "PayOff/Parameters.h"
#include "Random/Random.h"
#include "Statistics/Statistics.h"
#include "PayOff/Vanilla.h"

__declspec(dllexport) void SimpleMonteCarlo(const VanillaOption& option, double spot, const Parameters& vol, const Parameters& r, ulong numPaths, StatisticsMC& gatherer);
__declspec(dllexport) void SimpleMonteCarlo(const VanillaOption & option, double spot, const Parameters & vol, const Parameters & r, ulong numPaths, StatisticsMC & gatherer, RandomBase & generator);