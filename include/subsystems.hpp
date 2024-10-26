#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

//Motors, sensors, etc
inline pros::MotorGroup intake({6, -4});
inline ez::Piston mogomech('G');
inline ez::Piston ringclamp('A');
inline ez::Piston wallmech('B');
inline pros::Optical ringsens(8);
// inline pros::adi::DigitalIn limit_switch('A');

//Functions
void colorDetect();
void colorProbe();
void allianceProbe();
void setIntake();
void setMogo();
void setClamp();
void setWall();
bool shift();

//auton subsystems

void redAssign();
void blueAssign();
void neutralAssign();
void discard();
void ringsensTask();
