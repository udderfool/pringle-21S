#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "pros/motor_group.hpp"
#include "subsystems.hpp"

//passive (running in driver and auton)
void colorDetect();
void colorProbe();
void allianceProbe();
void ringsensTask();

//auton functions
void redAssign();
void blueAssign();
void neutralAssign(); //applied during driver and during certain sections of auton- stops discard code from triggering
void discard();
void discardSafetySet();
void discardNormalSet();