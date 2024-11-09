#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "autons.hpp" //this is our autons header files yours might be called something different

void screeninit();
static void jasassign();
static void switches();
static void updownbtn();
static void selectauton();
static void updownbtn();
static void jasautonselector();
namespace jas {
//vector that stores the description of the auton- make sure it matches with the main list
static std::vector<std::string> jasDESC = {
      "blue 50% wp",
      "at-home testing for \nblue auton",
      "Move forward",
      "skills",
      "red 50% wp",
      "at-home testing for \nred auton",
      "Move forward",
      "skills",
      "blue 4 ring no WP",
      "blue 4 ring wp \n(DO NOT RUN)",
      "blue 6 ring no WP",
      "Move forward",
      "skills",
      "red 4 ring no WP",
      "red 4 ring wp \n(DO NOT RUN)",  
      "red 6 ring no WP",
      "Move forward",
      "skills"
      };

//the main auton vector- now that im looking at it again, it probably doesnt need to store the autons themselves,
//because they are added to the ez auton selector code in main.cpp. probably gonna rewrite all of this to be a single vector
//that stores two strings, instead of how it is now. anyways, what is stored here is the void name of the auton
static std::vector<Auton> jasNAME = {
      Auton("blue_50WP", blue_50WP),
      Auton("testautonBlue", testautonBlue),
      Auton("move_forward", move_forward),
      Auton("skills", skills),
      Auton("red_50WP", red_50WP),
      Auton("testautonRed", testautonRed),
      Auton("move_forward", move_forward),
      Auton("skills", skills),
      Auton("blue_4greed", blue_4greed),
      Auton("blue_4ring", blue_4ring),
      Auton("blue_6ring", blue_6ring),
      Auton("move_forward", move_forward),
      Auton("skills", skills),
      Auton("red_4greed", red_4greed),
      Auton("red_4ring", red_4ring),
      Auton("red_6ring", red_6ring),
      Auton("move_forward", move_forward),
      Auton("skills", skills)
      };
    }