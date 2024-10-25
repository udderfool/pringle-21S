#include "subsystems.hpp"
#include "main.h"
#include "pros/colors.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"
#include <string>

std::string intakeColor = "neutral";

void colorDetect() {
  if ((ringsens.get_hue() < 30) && (ringsens.get_hue() > 1)) {
    intakeColor = "red";
  } else if ((ringsens.get_hue() < 240) && (ringsens.get_hue() > 180)) {
    intakeColor = "blue";
  } else {
    intakeColor = "neutral";
  }
}

pros::Task colordetection(colorDetect);

void colorProbe() {
  if (intakeColor == "red") {
    pros::screen::set_pen(pros::Color::red);
    pros::screen::fill_rect(0,0,400,200);
  } else if (intakeColor == "blue") {
    pros::screen::set_pen(pros::Color::blue);
    pros::screen::fill_rect(0,0,400,200);
  } else if (intakeColor == "neutral") {
    pros::screen::set_pen(pros::Color::yellow);
    pros::screen::fill_rect(0,0,400,200);
  }
}

pros::Task colorprobing(colorProbe);

void setIntake() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    intake.move(127);
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    intake.move(-127);
  } else {
    intake.move(0);
  }
}

void setMogo() {
    mogomech.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_B));
}

void setWall() {
  wallmech.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
}
//temp code for test or something idk
void setClamp() {
  ringclamp.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1));
  /*
  //if trigger button and optical sensor (red or blue) are true, then set clamp after [x] ms
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    if (intakeColor == "red" || intakeColor == "blue") {
      ringclamp.set(true);
    }
  }
  if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    ringclamp.set(false);
  }
  */
}

bool shift() { 
  return master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
}

//auton subsystems

//variable changed during auton and driver to determine red/blue/no alliance selection
char allianceColor = 'A';

void discard() {
  ringclamp.set(true);
  pros::delay(500);
  wallmech.set(true);
  pros::delay(500);
  ringclamp.set(false);
  wallmech.set(false);
}

void ringsensTask() {
  if ((allianceColor == 'R' && intakeColor == "blue") || (allianceColor == 'B' && intakeColor == "red"))  {
      discard();
  }
}

pros::Task ringsort(ringsensTask);