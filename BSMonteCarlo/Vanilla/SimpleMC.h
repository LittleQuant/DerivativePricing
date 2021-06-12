#pragma once

typedef unsigned long ulong;

#include "../Utility/Parameters.h"
#include "../Random/Random.h"
#include "../Statistics/Statistics.h"
#include "Vanilla.h"

__declspec(dllexport) void SimpleMonteCarlo(const VanillaOption& option, double spot, const Parameters& vol, const Parameters& r, ulong numPaths, StatisticsMC& gatherer);
__declspec(dllexport) void SimpleMonteCarlo(const VanillaOption & option, double spot, const Parameters & vol, const Parameters & r, ulong numPaths, StatisticsMC & gatherer, RandomBase & generator);