#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

void tempcheck();
void tempcheckctrl();
static void gettemp(lv_event_t *e);

namespace jas {
class motors {
   public:
	struct motordata {
		char index;
		pros::Motor motor;
		std::string name;
	};
};
}  // namespace jas

extern vector<jas::motors::motordata> motorbar;
extern vector<lv_obj_t *> motorboxes;
extern lv_obj_t *mainlabel;