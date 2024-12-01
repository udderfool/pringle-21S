#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

void screeninit();
void jautonrun();
static void listupdate();
static void clear();
static void jautoncurate(lv_event_t* e);
static void selectauton(lv_event_t* e);
static void updownbtn(lv_event_t* e);
static void pageswitchbtn(lv_event_t* e);

extern lv_obj_t* autoselector;
extern lv_obj_t* motortemps;
extern lv_obj_t* pageswitch;

extern bool noselection;
namespace jas {
class jasauton {
   public:
	jasauton();
	jasauton(std::function<void()> autoncall, int redblufilt, int posnegfilt, std::string name, std::string desc, int mogo1, int mogo2, bool allyring);
	std::function<void()> AutonCall;
	int RedBluFilt;
	int PosNegFilt;
	std::string Name;
	std::string Desc;
	int Mogo1;
	int Mogo2;
	bool AllyRing;
};

class jautontable {
   public:
	std::vector<jasauton> jasautontable;
	void jautonpopulate(std::vector<jasauton> JasAutonTable);
};
}  // namespace jas
extern jas::jautontable j_auton_selector;
extern vector<jas::jasauton> jautoncurated;