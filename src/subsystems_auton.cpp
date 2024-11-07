#include "subsystems_auton.hpp"
#include "EZ-Template/util.hpp"
#include "liblvgl/widgets/lv_switch.h"
#include "main.h"
#include "pros/colors.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"
#include <string>

std::string intakeColor = "neutral";
char allianceColor = 'A';
bool discardSwitch;


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
    mogomech.set(false);
    intake.move(20);
    pros::delay(500);
    intake.move(-127);
    pros::delay(500);
    mogomech.set(true);
    intake.move(0);
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