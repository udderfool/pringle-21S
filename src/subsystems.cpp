#include "subsystems.hpp"
#include "main.h"
#include "pros/misc.h"

using pros::E_CONTROLLER_DIGITAL_B;
using pros::E_CONTROLLER_DIGITAL_DOWN;
using pros::E_CONTROLLER_DIGITAL_L1;
using pros::E_CONTROLLER_DIGITAL_L2;
using pros::E_CONTROLLER_DIGITAL_R1;
using pros::E_CONTROLLER_DIGITAL_R2;

void setIntake() {
  if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
    intake.move(127);
  } else if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
    intake.move(-127);
  } else {
    intake.move(0);
  }
}

void setMogo() {
    mogomech.button_toggle(master.get_digital(E_CONTROLLER_DIGITAL_B));
}

void setWall() {
  if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
    wallmech.set(true);
  } else {
    wallmech.set(false);
  }
}

void setClamp() {
  //if trigger button and optical sensor (red or blue) are true, then set clamp after [x] ms
  while (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
    if (ringsens.get_hue() < 240) {
      ringclamp.set(true);
    }
  }
  if (!master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
    ringclamp.set(false);
  }
}

bool shift() { 
  return master.get_digital(E_CONTROLLER_DIGITAL_R1);
}