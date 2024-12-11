#include "autonbuilder.hpp"
#include "main.h"

void testautonbuilder() {
    pros::Task ringsort(ringsensTask, (void*)"R");
    red_neg_mogo();
    red_neg_btmringstack();
    red_midneg_2ring();
    red_mid_topringstack();
    red_alliancestake();
    ladder();
}

void red_midneg_2ring() {
    intake.move(-127);
    chassis.pid_odom_set({{{18_in, 61_in, 0_deg}, fwd, 127}, {{34_in, 63_in}, fwd, 60}});
    chassis.pid_wait();
}

void red_neg_btmringstack() {
    intake.move(-127);
    chassis.pid_odom_set({{24_in, 48_in}, fwd, 127});
    chassis.pid_wait();
}

void red_neg_mogo() {
    chassis.odom_pose_set({48_in, 21_in, 180_deg});
    chassis.pid_odom_set({{48_in, 46_in}, rev, 127});
    chassis.pid_wait_quick_chain();
    mogomech.set(true);
    chassis.pid_odom_set({{48_in, 48_in}, rev, 127});
    chassis.pid_wait();
}

void red_neg_corner() {
    //corner rush
}

void red_mid_topringstack() {
    intakeLevel.set(true);
    intake.move(-127);
    chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
    intakeLevel.set(false);
    chassis.pid_wait();
}

void red_alliancestake() {
    intake.move(0);
    chassis.pid_odom_set({{{72_in, 24_in, 180_deg}, fwd, 127}, {{72_in, 0_in}, rev, 70}});
    intake.move(-127);
    chassis.pid_wait();
}

void red_pos_btmringstack() {
    intake.move(-127);
    chassis.pid_odom_set({{120_in, 48_in}, fwd, 127});
    chassis.pid_wait();
}

void red_pos_mogo() {
    chassis.pid_odom_set({{96_in, 46_in}, rev, 127});
    chassis.pid_wait_quick_chain();
    mogomech.set(true);
    chassis.pid_odom_set({{96_in, 48_in}, rev, 127});
    chassis.pid_wait();
}

void red_midpos_mogo() {
    //goal rush
}

void red_pos_corner() {
    //corner rush
}

void ladder() {
    pros::delay(2000);
    intake.move(127);
    chassis.pid_odom_set({{72_in, 72_in}, fwd, 127});
    chassis.pid_wait();
}

void blue_midneg_2ring() {
    intake.move(-127);
    chassis.pid_odom_set({{{126_in, 61_in, 0_deg}, fwd, 127}, {{110_in, 63_in}, fwd, 60}});
    chassis.pid_wait();
}

void blue_neg_btmringstack() {
    intake.move(-127);
    chassis.pid_odom_set({{120_in, 48_in}, fwd, 127});
    chassis.pid_wait();
}

void blue_neg_mogo() {
    chassis.pid_odom_set({{96_in, 46_in}, rev, 127});
    chassis.pid_wait_quick_chain();
    mogomech.set(true);
    chassis.pid_odom_set({{96_in, 48_in}, rev, 127});
    chassis.pid_wait();
}

void blue_neg_corner() {
    //corner rush
}

void blue_mid_topringstack() {
    intakeLevel.set(true);
    intake.move(-127);
    chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
    intakeLevel.set(false);
    chassis.pid_wait();
}

void blue_alliancestake() {
    intake.move(0);
    chassis.pid_odom_set({{{72_in, 24_in, 180_deg}, fwd, 127}, {{72_in, 0_in}, rev, 70}});
    intake.move(-127);
    chassis.pid_wait();
}

void blue_pos_btmringstack() {
    intake.move(-127);
    chassis.pid_odom_set({{24_in, 48_in}, fwd, 127});
    chassis.pid_wait();
}

void blue_pos_mogo() {
    chassis.odom_pose_set({48_in, 21_in, 180_deg});
    chassis.pid_odom_set({{48_in, 46_in}, rev, 127});
    chassis.pid_wait_quick_chain();
    mogomech.set(true);
    chassis.pid_odom_set({{48_in, 48_in}, rev, 127});
    chassis.pid_wait();
}

void blue_midpos_mogo() {
    //goal rush
}

void blue_pos_corner() {
    //corner rush
}