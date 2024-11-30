#pragma once

#include "api.h"
#include "EZ-Template/api.hpp"

void tempcheck();
void tempcheckctrl();
static void gettemp(lv_event_t * e);

namespace jas {
    class motors {
        public:
        struct motordata {
            int port;
            pros::Motor motor;
            std::string name;
        };
    };
}

extern vector<jas::motors::motordata> motorbar;