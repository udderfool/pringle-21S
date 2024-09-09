#include "main.h"

void setIntake() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    intake.move(127);
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    intake.move(-127);
  } else {
    intake.move(0);
  }
}

void setMogo() {
    mogomech.button_toggle(master.get_digital(DIGITAL_B));
}

bool shift() {
  return master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
}
