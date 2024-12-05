#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our
// website! https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;
const int GRAB_MOGO = 55;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  // https://ez-robotics.github.io/EZ-Template/tutorials/tuning_constants
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  // https://ez-robotics.github.io/EZ-Template/tutorials/tuning_exit_conditions
  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  // https://ez-robotics.github.io/EZ-Template/tutorials/slew_constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(7_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void testtestest() {
  chassis.odom_pose_set({10_in, 0_in, 0_deg});
  chassis.pid_odom_set({{{0_in, 40_in}, fwd}, {{20_in, 60_in}, fwd}});
}

void move_forward() { chassis.pid_drive_set(5_in, DRIVE_SPEED, true); }
// RED
/*void red_WP(){
  //Get mogo and score 2 rings
  mogomech.set(false);
  chassis.pid_drive_set(-32_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-22.75_in);
  mogomech.set(true);
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(127);
  chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  //drop off mogo and drive to other one
  chassis.pid_drive_set(-5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(66_deg, TURN_SPEED);
  chassis.pid_wait();
  mogomech.set(false);
  intake.move(0);
  chassis.pid_drive_set(46.125_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(127);
  chassis.pid_drive_set(-35_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-22_in);
  mogomech.set(true);
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(24_in, DRIVE_SPEED, false);
  chassis.pid_wait_until(20_in);
  chassis.pid_wait();
  chassis.pid_drive_set(-48_in, DRIVE_SPEED, true);
}*/
void testautonRed() {
	pros::Task ringsort(ringsensTask);
	redAssign();
	lv_obj_t *gyat = lv_obj_create(autoselector);
	lv_obj_set_style_bg_color(gyat, lv_color_hex(0x42f548), LV_PART_MAIN);
	lv_obj_set_size(gyat, 20, 20);
	lv_obj_set_scrollbar_mode(gyat, LV_SCROLLBAR_MODE_OFF);
	intake.move(-127);
	chassis.pid_wait();
}

void testcolorsortRed() {
	pros::Task ringsort(ringsensTask);
	redAssign();
	intake.move(-127);
	chassis.pid_drive_set(60_in, 32, false);
	chassis.pid_wait();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(20_in, 32, false);
	chassis.pid_wait();
	chassis.pid_turn_set(135_deg, TURN_SPEED);
	wallmech.move_relative(-700, -127);
}

void testautonBlue() {
	pros::Task ringsort(ringsensTask);
	blueAssign();
	lv_obj_t *gyat2 = lv_obj_create(autoselector);
	lv_obj_set_style_bg_color(gyat2, lv_color_hex(0xa442f5), LV_PART_MAIN);
	lv_obj_set_scrollbar_mode(gyat2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_size(gyat2, 20, 10);
	mogomech.set(true);
	chassis.pid_wait();
}

void testcolorsortBlue() {
	pros::Task ringsort(ringsensTask);
	redAssign();
	intake.move(-127);
	chassis.pid_drive_set(60_in, 32, false);
	chassis.pid_wait();
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(20_in, 32, false);
	chassis.pid_wait();
	chassis.pid_turn_set(-135_deg, TURN_SPEED);
	wallmech.move_relative(-700, -127);
}

void red_50WP() {
	// pros::Task ringsort(ringsensTask);
	// redAssign();
	// Get mogo and score 2 rings
	mogomech.set(false);
	chassis.pid_drive_set(-34_in, 75, true);
	chassis.pid_wait_until(-23.5_in);
	mogomech.set(true);
	chassis.pid_wait();
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait();
	intake.move(-127);
	chassis.pid_drive_set(22_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	// drop off mogo and touch mid
	pros::delay(2000);
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(48_in, 75, true);
	chassis.pid_wait();
	if(!chassis.interfered) {
		intake.move(0);
		return;
	}
	intake.move(0);
	wallmech.move_relative(-500, -127);
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	neutralAssign();
	chassis.pid_wait();
}

void red_4ring() {
	// pros::Task ringsort(ringsensTask);
	// redAssign();
	// wallmech.move_relative(-100, -127);
	// score on allaince stake
	chassis.pid_drive_set(-15_in, DRIVE_SPEED, false);
	chassis.pid_wait_until(-8_in);
	chassis.pid_wait();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(-12_in, DRIVE_SPEED, false);
	intake.move(-127);
	chassis.pid_wait();
	pros::delay(150);
	chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(225_deg, TURN_SPEED);	// turn to mogo -135
	chassis.pid_wait();
	chassis.pid_drive_set(-34_in, 75, true);  // used to be 35 inches
	chassis.pid_wait_until(-32.75_in);
	mogomech.set(true);
	chassis.pid_wait();
	chassis.pid_turn_set(0_deg, TURN_SPEED);  // turn to rings
	chassis.pid_wait();
	chassis.pid_drive_set(28_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_drive_set(-1_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-12_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(8.75_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-3_in, DRIVE_SPEED, true);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(180_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	wallmech.move_relative(500, -127);
	chassis.pid_drive_set(50_in, DRIVE_SPEED, true);
	neutralAssign();
	chassis.pid_wait();
}

void red_4greed() {
	// pros::Task ringsort(ringsensTask);
	// redAssign();
	// wallmech.move_relative(-100, -127);
	chassis.pid_drive_set(-30_in, 60, true);
	chassis.pid_wait_until(-27.5_in);
	mogomech.set(true);
	chassis.pid_wait();
	intake.move(-127);
	chassis.pid_turn_set(90_deg, TURN_SPEED);  // turn to rings
	chassis.pid_wait();
	chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_relative_set(95_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(14_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	pros::delay(500);
	chassis.pid_wait();
	chassis.pid_drive_set(-8_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(225_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(14_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	wallmech.move_relative(-500, -127);
	chassis.pid_drive_set(50_in, DRIVE_SPEED, true);
	neutralAssign();
	chassis.pid_wait();
}

void red_6ring() {
	// pros::Task ringsort(ringsensTask);
	// redAssign();
	// wallmech.move_relative(-100, -127);
	chassis.pid_drive_set(-30_in, 60, true);
	chassis.pid_wait_until(-27_in);
	mogomech.set(true);
	chassis.pid_wait();
	intake.move(-127);
	chassis.pid_turn_set(90_deg, TURN_SPEED);  // turn to rings
	chassis.pid_wait();
	chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(23_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(34_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(185_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_drive_set(-8_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(225_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	wallmech.move_relative(500, -127);
	chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
	neutralAssign();
	chassis.pid_wait();
}

// BLUE

/*void blue_WP(){
  //Get mogo and score 2 rings
  mogomech.set(false);
  chassis.pid_drive_set(-35_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-22.75_in);
  mogomech.set(true);
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(127);
  chassis.pid_drive_set(22_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  //drop off mogo and drive to other one
  chassis.pid_drive_set(-5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-66_deg, TURN_SPEED);
  chassis.pid_wait();
  mogomech.set(false);
  intake.move(0);
  chassis.pid_drive_set(45.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(127);
  chassis.pid_drive_set(-35_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-21_in);
  mogomech.set(true);
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(24_in, DRIVE_SPEED, false);
  chassis.pid_wait_until(20_in);
  chassis.pid_wait();
  chassis.pid_drive_set(-48_in, DRIVE_SPEED, true);
}*/

void blue_50WP() {
	// pros::Task ringsort(ringsensTask);
	// blueAssign();
	// Get mogo and score 2 rings
	mogomech.set(false);
	chassis.pid_drive_set(-35_in, 60, true);
	chassis.pid_wait_until(-22.75_in);
	mogomech.set(true);
	chassis.pid_wait();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
	intake.move(-127);
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	// drop off mogo and touch mid
	pros::delay(2000);
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait();
	pros::delay(1500);
	mogomech.set(false);
	intake.move(0);
	chassis.pid_drive_set(48_in, 75, true);
	chassis.pid_wait();
	if(!chassis.interfered) {
		return;
	}
	wallmech.move_relative(-500, -127);
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	neutralAssign();
	chassis.pid_wait();
}

void blue_4ring() {
	// pros::Task ringsort(ringsensTask);
	// blueAssign();
	// wallmech.move_relative(-100, -127);
	// score on allaince stake
	chassis.pid_drive_set(-16_in, DRIVE_SPEED, false);
	chassis.pid_wait_until(-8_in);
	chassis.pid_wait();
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait();
	intake.move(-127);
	pros::delay(250);
	chassis.pid_drive_set(-12_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	pros::delay(150);
	chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(-225_deg, TURN_SPEED);	 // turn to mogo 135
	chassis.pid_wait();
	chassis.pid_drive_set(-34_in, 75, true);  // used to be 35 inches
	chassis.pid_wait_until(-32_in);
	mogomech.set(true);
	chassis.pid_wait();
	chassis.pid_turn_set(0_deg, 75);  // turn to rings
	chassis.pid_wait();
	chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(9_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-9_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-7_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(14_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	pros::delay(200);
	chassis.pid_drive_set(-8_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	wallmech.move_relative(500, -127);
	chassis.pid_drive_set(50_in, DRIVE_SPEED, true);
	neutralAssign();
	chassis.pid_wait();
}

void blue_4greed() {
	// pros::Task ringsort(ringsensTask);
	// blueAssign();
	// wallmech.move_relative(-100, -127);
	chassis.pid_drive_set(-30_in, 60, true);
	chassis.pid_wait_until(-27.5_in);
	mogomech.set(true);
	chassis.pid_wait();
	intake.move(-127);
	chassis.pid_turn_set(-90_deg, TURN_SPEED);	// turn to rings
	chassis.pid_wait();
	chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_relative_set(-95_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_wait();
	chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	pros::delay(500);
	chassis.pid_drive_set(-12, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(-225_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(14_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(-8, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	wallmech.move_relative(-500, -127);
	chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
	neutralAssign();
	chassis.pid_wait();
}

void blue_6ring() {
	// pros::Task ringsort(ringsensTask);
	// blueAssign();
	// wallmech.move_relative(-100, -127);
	chassis.pid_drive_set(-30_in, 75, true);
	chassis.pid_wait_until(-28_in);
	mogomech.set(true);
	chassis.pid_wait();
	intake.move(-127);
	chassis.pid_turn_set(-90_deg, TURN_SPEED);	// turn to rings
	chassis.pid_wait();
	chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(-20_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(40_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
	pros::delay(500);
	chassis.pid_drive_set(-10_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(-190_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(36_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_drive_set(-4_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(-225_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(4_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_drive_set(-4, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	wallmech.move_relative(500, -127);
	chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
	neutralAssign();
	chassis.pid_wait();
}

// SKILLS

void skills() {
	chassis.pid_drive_set(-2_in, 60, false);
	mogomech.set(true);	 // grab top left mogo
	intake.move(-127);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-28_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_turn_set(-135_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(66_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(-56_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(43.25_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(153_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(26.75_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	pros::delay(2000);
	mogomech.set(false);
	intake.move(0);
	chassis.pid_turn_set(-64_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-53_in, 75, true);
	chassis.pid_wait_until(-48_in);
	mogomech.set(true);	 // grab center right mogo
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
	intake.move(-127);
	chassis.pid_drive_set(36_in, 100, true);
	chassis.pid_wait();
	chassis.pid_drive_set(-12_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(45_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(34_in, DRIVE_SPEED, true);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(84_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	pros::delay(1000);
	chassis.pid_turn_set(135_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(16.5_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	pros::delay(2000);
	mogomech.set(false);
	chassis.pid_turn_set(180_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	pros::delay(200);
	intake.move(0);
	chassis.pid_turn_set(-36_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(60_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(-48_in, 75, true);
	chassis.pid_wait_until(-44_in);
	mogomech.set(true);	 // grab bottom left mogo
	chassis.pid_wait();
	intake.move(-127);
	chassis.pid_turn_set(180_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(24_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(24_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(20_in, 90, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(10_in, 90, false);
	chassis.pid_wait();
	pros::delay(1000);
	chassis.pid_turn_set(17_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(16.5_in, 90, false);
	chassis.pid_wait();
	chassis.pid_turn_set(180_deg, TURN_SPEED);
	chassis.pid_wait();
	pros::delay(2000);
	mogomech.set(false);
	chassis.pid_drive_set(98_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	pros::delay(200);
	intake.move(0);
	chassis.pid_turn_set(15_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(89.5_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(24_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait();
	intake.move(-127);
	pros::delay(250);
	chassis.pid_drive_set(14_in, DRIVE_SPEED, false);
}

void skills50() {
	chassis.pid_drive_set(-18_in, 60, false);
	chassis.pid_wait_until(-4_in);
	mogomech.set(true);
	intake.move(-127);
	chassis.pid_wait();
	chassis.pid_turn_set(-90_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	pros::delay(500);
	chassis.pid_turn_set(-180_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(24_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(24_in, DRIVE_SPEED, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(310_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(40_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(113_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(-14_in, 90, false);
	mogomech.set(false);
	intake.move(0);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(135_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(85_in, 90, true);
	chassis.pid_wait_until(75_in);
	intake.move_relative(-2500, -127);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(45_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(34_in, DRIVE_SPEED, true);
	chassis.pid_wait_until(30_in);
	intake.move_relative(-2500, -127);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(180_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(-24_in, 60, false);
	chassis.pid_wait_until(-19_in);
	mogomech.set(true);
	intake.move(-127);
	chassis.pid_wait();
	chassis.pid_turn_set(135_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(34_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	pros::delay(1000);
	chassis.pid_turn_set(105_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(6_in, 40, false);
	chassis.pid_wait();
	pros::delay(1000);
	chassis.pid_turn_set(208_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-8_in, 80, false);
	mogomech.set(false);
	chassis.pid_wait();
	chassis.pid_turn_set(183_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	indexer.set(true);
	intake.move(-127);
	chassis.pid_drive_set(62_in, 90, true);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_turn_relative_set(360_deg, 127);
	chassis.pid_wait();
	wallmech.move_absolute(-700, -90);
	indexer.set(false);
	pros::delay(1000);
	chassis.pid_drive_set(8_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	wallmech.move_absolute(0, 90);
	chassis.pid_drive_set(-14_in, 75, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(180_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait_until(19_in);
	intake.move_relative(-2500, -127);
	chassis.pid_wait();
	pros::delay(1000);
	chassis.pid_turn_set(270_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait_until(19_in);
	intake.move_relative(-2500, -127);
	chassis.pid_wait();
	pros::delay(1000);
	chassis.pid_turn_set(45_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(-34_in, 60, true);
	chassis.pid_wait_until(30_in);
	mogomech.set(true);
	intake.move_relative(-2500, -127);
	chassis.pid_wait();
	pros::delay(500);
	mogomech.set(false);
	chassis.pid_turn_set(180_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(16_in, 90, false);
	intake.move(-127);
	chassis.pid_wait();
	pros::delay(1000);
	chassis.pid_drive_set(-6_in, 60, false);
	chassis.pid_wait();
	chassis.pid_turn_set(95_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(56_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(26_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(12_in, 75, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(267_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_drive_set(114_in, DRIVE_SPEED, true);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(0_deg, TURN_SPEED);
	indexer.set(true);
	intake.move(-127);
	chassis.pid_wait();
	chassis.pid_drive_set(60_in, DRIVE_SPEED, true);
	chassis.pid_wait_until(58_in);
	intake.move(false);
	chassis.pid_wait();
	chassis.pid_turn_set(270_deg, TURN_SPEED);
	chassis.pid_wait();
	chassis.pid_turn_relative_set(360_deg, 127);
	chassis.pid_wait();
	wallmech.move_absolute(-700, -90);
	indexer.set(false);
	pros::delay(1000);
	chassis.pid_drive_set(8_in, DRIVE_SPEED, false);
	chassis.pid_wait();
	wallmech.move_absolute(0, 90);
	chassis.pid_drive_set(-8_in, 75, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(48_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(74_in, DRIVE_SPEED, true);
	chassis.pid_wait();
	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();
	chassis.pid_drive_set(16_in, 75, false);
	chassis.pid_wait_until(8_in);
	intake.move(-127);
	chassis.pid_wait();
}

///
// Drive Example
///
void drive_example() {
	// The first parameter is target inches
	// The second parameter is max speed the robot will drive at
	// The third parameter is a boolean (true or false) for enabling/disabling a
	// slew at the start of drive motions for slew, only enable it when the drive
	// distance is greater than the slew distance + a few inches

	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait();

	chassis.pid_drive_set(-12_in, DRIVE_SPEED);
	chassis.pid_wait();

	chassis.pid_drive_set(-12_in, DRIVE_SPEED);
	chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
	// The first parameter is the target in degrees
	// The second parameter is max speed the robot will drive at

	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_turn_set(45_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait();

	chassis.pid_turn_set(45_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_turn_set(-45_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
	chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
	// pid_wait_until will wait until the robot gets to a desired position

	// When the robot gets to 6 inches slowly, the robot will travel the remaining
	// distance at full speed
	chassis.pid_drive_set(24_in, 30, true);
	chassis.pid_wait_until(6_in);
	chassis.pid_speed_max_set(DRIVE_SPEED);	 // After driving 6 inches at 30 speed, the robot will go the
											 // remaining distance at DRIVE_SPEED
	chassis.pid_wait();

	chassis.pid_turn_set(45_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_turn_set(-45_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait();

	// When the robot gets to -6 inches slowly, the robot will travel the
	// remaining distance at full speed
	chassis.pid_drive_set(-24_in, 30, true);
	chassis.pid_wait_until(-6_in);
	chassis.pid_speed_max_set(DRIVE_SPEED);	 // After driving 6 inches at 30 speed, the robot will go the
											 // remaining distance at DRIVE_SPEED
	chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
	// The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
	// The second parameter is the target in degrees
	// The third parameter is the speed of the moving side of the drive
	// The fourth parameter is the speed of the still side of the drive, this
	// allows for wider arcs

	chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
	chassis.pid_wait();

	chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
	chassis.pid_wait();

	chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
	chassis.pid_wait();

	chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
	chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
	// Motion chaining is where motions all try to blend together instead of
	// individual movements. This works by exiting while the robot is still moving
	// a little bit. To use this, replace pid_wait with pid_wait_quick_chain.
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait();

	chassis.pid_turn_set(45_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();

	chassis.pid_turn_set(-45_deg, TURN_SPEED);
	chassis.pid_wait_quick_chain();

	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait();

	// Your final motion should still be a normal pid_wait
	chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
	chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait();

	chassis.pid_turn_set(45_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
	chassis.pid_wait();

	chassis.pid_turn_set(0_deg, TURN_SPEED);
	chassis.pid_wait();

	chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
	chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
	for(int i = 0; i < attempts - 1; i++) {
		// Attempt to drive backward
		printf("i - %i", i);
		chassis.pid_drive_set(-12_in, 127);
		chassis.pid_wait();

		// If failsafed...
		if(chassis.interfered) {
			chassis.drive_sensor_reset();
			chassis.pid_drive_set(-2_in, 20);
			pros::delay(1000);
		}
		// If the robot successfully drove back, return
		else {
			return;
		}
	}
}

// If there is no interference, the robot will drive forward and turn 90
// degrees. If interfered, the robot will drive forward and then attempt to
// drive backward.
void interfered_example() {
	chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
	chassis.pid_wait();

	if(chassis.interfered) {
		tug(3);
		return;
	}

	chassis.pid_turn_set(90_deg, TURN_SPEED);
	chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .