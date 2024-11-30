#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

//Motors, sensors, etc
inline pros::MotorGroup intake({6, 4});
inline pros::Motor wallmech(21);
inline ez::Piston mogomech('G');
inline ez::Piston indexer('A');
inline pros::Optical ringsens(8);
inline ez::Piston doinker('C');
// inline pros::adi::DigitalIn limit_switch('A');

//Functions
void setIntake();
void setMogo();
void setRedirect();
void setWall();
bool shift();
void setdoinker();