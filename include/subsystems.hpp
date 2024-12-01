#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

// Motors, sensors, etc
inline pros::MotorGroup intake({6, 4});
inline pros::Motor wallmech(21);
inline ez::Piston mogomech('G');
inline ez::Piston indexer('A');
inline pros::Optical ringsens(8);
inline ez::Piston doinker('C');
// inline pros::adi::DigitalIn limit_switch('A');

// Functions
void setIntake();
void setMogo();
void setRedirect();
void setWall();
bool shift();
void setdoinker();