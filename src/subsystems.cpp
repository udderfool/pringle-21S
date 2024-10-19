#include "main.h"
#include "pros/misc.h"

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
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    wallmech.set(true);
  } else {
    wallmech.set(false);
  }
}
//temp code for test or something idk
void setClamp() {
  //if trigger button and optical sensor (red or blue) are true, then set clamp after [x] ms
  /*while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    if (ringsens.get_hue() < 240) {
      ringclamp.set(true);
    }
  }*/
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    ringclamp.set(false);
  }
  if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    ringclamp.set(true);
  }
}

bool shift() { 
  return master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
}