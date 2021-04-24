#pragma once

#include <cmath>

typedef unsigned long ulong;

#include "Parameters.h"
#include "Statistics.h"
#include "Vanilla.h"

void SimpleMonteCarlo(const VanillaOption& option, double spot, const Parameters& vol, const Parameters& r, ulong numPaths, StatisticsMC& gatherer);