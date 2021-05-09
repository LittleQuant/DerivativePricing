#pragma once

typedef unsigned long ulong;

#include "Parameters.h"
#include "Statistics.h"
#include "Vanilla.h"

extern "C" __declspec(dllexport) void SimpleMonteCarlo(const VanillaOption& option, double spot, const Parameters& vol, const Parameters& r, ulong numPaths, StatisticsMC& gatherer);