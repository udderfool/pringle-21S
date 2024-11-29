#include "main.h"
#include "pros/device.h"
#include "pros/motor_group.hpp"
#include "pros/optical.hpp"
#include <cstdint>

//use iterator to create label objects, and to set some variable or something for each of them to track a motor
vector<int8_t> motorportsbar {};

pros::MotorGroup motorports({motorportsbar});

void tempcheck() {
    for(int a = 1; a < 22; a++) {
        int device = pros::c::get_plugged_type(a);
        printf("device plugged type: {plugged type: %d}\n", device);
        if(device == 16) motorportsbar.push_back(a);
    } 
    printf("motor port count: {port count: %d}\n", motorportsbar.size());
    printf("motor port: {port number: %hhd}\n", motorportsbar[0]);
}