#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

//Motors, sensors, etc
inline pros::MotorGroup intake({6, 4});
inline pros::MotorGroup wallmech({19});
inline ez::Piston mogomech('G');
inline ez::Piston redirect('A');
inline pros::Optical ringsens(8);
// inline pros::adi::DigitalIn limit_switch('A');

//Functions
void setIntake();
void setMogo();
void setRedirect();
void setWall();
bool shift();