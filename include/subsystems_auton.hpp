#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

// passive (running in driver and auton)
void colorDetect();
void colorProbe();
void allianceProbe();
void ringsensTask(void* assign);

// auton functions
void discard();
void discardSafetySet();
void discardNormalSet();