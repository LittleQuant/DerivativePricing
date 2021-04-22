#pragma once

#include <cmath>

typedef unsigned long ulong;

#include "Parameters.h"
#include "Vanilla.h"

double SimpleMonteCarlo2(const VanillaOption& option, double spot, const Parameters& vol, const Parameters& r, ulong numPaths);