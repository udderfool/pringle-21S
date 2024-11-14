#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "autons.hpp" //this is our autons header files yours might be called something different
#include <string>

void screeninit();
static void jasassign();
static void switches();
static void updownbtn();
static void selectauton();
static void updownbtn();
static void jasautonselector();
namespace jas {
    class jasauton {
 public:
  std::string Name;
  std::string Desc;
  std::function<void()> autonCall;
  jasauton(std::string name, std::string desc, std::function<void()> autoncall) {
    Name = name;
    Desc = desc;
    autonCall = autoncall;
    }
  };
}