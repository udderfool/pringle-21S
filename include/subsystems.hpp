#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"

//Motors, sensors, etc
inline pros::MotorGroup intake({6, -4});
inline ez::Piston mogomech('G');
// inline pros::adi::DigitalIn limit_switch('A');

//Functions
void setIntake();
void setMogo();
bool shift();