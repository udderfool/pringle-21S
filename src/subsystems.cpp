#include "subsystems.hpp"
#include "EZ-Template/util.hpp"
#include "liblvgl/llemu.hpp"
#include "liblvgl/widgets/lv_switch.h"
#include "main.h"
#include "pros/colors.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"
#include <string>

std::string intakeColor = "neutral";
char allianceColor = 'A';

void colorDetect() {
while(true) {
  if ((ringsens.get_hue() < 30) && (ringsens.get_hue() > 1)) {
    intakeColor = "red";
  } else if ((ringsens.get_hue() < 240) && (ringsens.get_hue() > 210)) {
    intakeColor = "blue";
  } else {
    intakeColor = "neutral";
  }
  pros::delay(10);
  }
}

void colorProbe() {
while(true) {
  if (intakeColor == "red") {
    pros::screen::set_pen(pros::Color::orange_red);
    pros::screen::print(pros::E_TEXT_MEDIUM, 330,45, "ring: red   ");
  } else if (intakeColor == "blue") {
    pros::screen::set_pen(pros::Color::medium_blue);
    pros::screen::print(pros::E_TEXT_MEDIUM, 330, 45, "ring: blue  ");
  } else if (intakeColor == "neutral") {
    pros::screen::set_pen(pros::Color::dark_olive_green);
    pros::screen::print(pros::E_TEXT_MEDIUM, 330, 45, "ring: none  ");
  }
  pros::delay(10);
  }
}
void allianceProbe() {
while(true) {
  if (allianceColor == 'R') {
    pros::screen::set_pen(pros::Color::orange_red);
    pros::screen::print(pros::E_TEXT_MEDIUM, 290, 30, "alliance: red   ");
  } else if (allianceColor == 'B') {
    pros::screen::set_pen(pros::Color::medium_blue);
    pros::screen::print(pros::E_TEXT_MEDIUM, 290, 30, "alliance: blue  ");
  } else if (allianceColor == 'A') {
    pros::screen::set_pen(pros::Color::dark_olive_green);
    pros::screen::print(pros::E_TEXT_MEDIUM, 290, 30, "alliance: driver");
  } 
  pros::delay(10);
  }
}

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

void redAssign() {
  allianceColor = 'R';
}

void blueAssign() {
  allianceColor = 'B';
}

void neutralAssign() {
  allianceColor = 'A';
}

bool discardSwitch;

void discardNormalSet() {
  discardSwitch = false;
  pros::screen::set_pen(pros::Color::white_smoke);
  pros::screen::print(pros::E_TEXT_MEDIUM, 310, 60, "normal discard");
}

void discardSafetySet() {
  discardSwitch = true;
  pros::screen::set_pen(pros::Color::white_smoke);
  pros::screen::print(pros::E_TEXT_MEDIUM, 310, 60, "safety discard");
}

void discard() {
  if (discardSwitch != true) {
  pros::screen::set_pen(pros::Color::white_smoke);
  pros::screen::print(pros::E_TEXT_MEDIUM, 330, 75, "ring thrown!");
  ringclamp.set(true);
  pros::delay(500);
  wallmech.set(true);
  pros::delay(500);
  ringclamp.set(false);
  wallmech.set(false);
  neutralAssign();
  pros::screen::print(pros::E_TEXT_MEDIUM, 330, 75, "            ");
  return;
  } else if (discardSwitch == true) {
    pros::screen::print(pros::E_TEXT_MEDIUM, 330, 75, "ring thrown!");
    intake.move(20);
    mogomech.set(false);
    chassis.pid_drive_set(6_in, 90, false);
    chassis.pid_wait_quick_chain();
    chassis.pid_turn_relative_set(45_deg, 90);
    intake.move(-127);
    chassis.pid_wait();
    pros::delay(500);
    chassis.pid_turn_relative_set(-45_deg, 90);
    chassis.pid_wait_quick_chain();
    chassis.pid_drive_set(-7_in, 90, false);
    chassis.pid_wait_until(-6_in);
    mogomech.set(true);
    neutralAssign();
    pros::screen::print(pros::E_TEXT_MEDIUM, 330, 75, "            ");
    return;
  }
}

void ringsensTask() {
while(true) {
  if ((allianceColor == 'R' && intakeColor == "blue") || (allianceColor == 'B' && intakeColor == "red"))  {
      discard();
  }
  pros::delay(10);
  }
  return;
}