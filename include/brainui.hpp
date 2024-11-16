#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"
#include "autons.hpp" //this is our autons header files yours might be called something different
#include <cstdint>
#include <string>

void screeninit();
static void jasassign();
static void switches();
static void updownbtn();
static void selectauton();
static void updownbtn();
static void jasautonselector();
extern bool noselection;
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
    class jautonselector {
 public:
  std::vector<jasauton> jasautontable;
  int autontable = 0;
  struct filters {
    int startValue;
    int range;
    } bluepos, redpos, blueneg, redneg;
  void jautonpopulate(std::vector<jasauton> JasAutonTable) {
    jasautontable = {};
    jasautontable.assign(JasAutonTable.begin(), JasAutonTable.end());
    };
  void jautonRun();
  };
  class uisetting {
 public:
 int mogodisp1;
 int mogodisp2;
const uint32_t red = 0xff2a00;
const uint32_t blue = 0x0066cc;
const uint32_t neutral = 0x5d5d5d;
  struct values {
    uint32_t jcolor;
    int jheight[6]{61, 48, 35, 23, 10, 0};
    //int jposition[6]{212, 200, 188, 176, 164, 150};
  } mogo1, mogo2, ally;
  void autondisplayset();
  void autondisplayset(int mogo_rings_1, int mogo_rings_2, uint32_t mogo_color_1, uint32_t mogo_color_2, uint32_t alliance_ring) {
    mogodisp1 = mogo_rings_1;
    mogodisp2 = mogo_rings_2;
    mogo1.jcolor = mogo_color_1;
    mogo2.jcolor = mogo_color_2;
    ally.jcolor = alliance_ring;
    if(mogodisp1 == 0) mogodisp1 = 6;
    if(mogodisp2 == 0) mogodisp2 = 6;
  }
  };
}
  extern jas::jautonselector j_auton_selector;
  extern jas::uisetting uivalues;
