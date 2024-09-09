#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "pros/motors.hpp"
// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(3);
inline pros::Motor intake_2(4);
inline pros::Motor intake_lift(5);
inline ez::Piston mogomech('G');
// inline pros::adi::DigitalIn limit_switch('A');