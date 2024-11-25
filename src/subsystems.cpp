#include "subsystems.hpp"
#include "EZ-Template/util.hpp"
#include "liblvgl/llemu.hpp"
#include "liblvgl/widgets/lv_switch.h"
#include "main.h"
#include "pros/colors.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"
#include <string>


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
  wallmech.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    wallmech.move_absolute(-750, -90);
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    wallmech.move_absolute(0, 90);
  } else {
    wallmech.brake();
  }
}
//temp code for test or something idk
void setRedirect() {
  indexer.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
  /*
  //if trigger button and optical sensor (red or blue) are true, then set clamp after [x] ms
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    if (intakeColor == "red" || intakeColor == "blue") {
      indexer.set(true);
    }
  }
  if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    indexer.set(false);
  }
  */
}

bool shift() { 
  return master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
}

