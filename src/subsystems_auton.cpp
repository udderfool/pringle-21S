#include "main.h"

std::string intakeColor = "neutral";
char allianceColor = 'A';
bool discardSwitch;
lv_obj_t* ringind = lv_obj_create(autoselector);
int spurfly;

void colorDetect() {
	while(true) {
		ringsens.set_led_pwm(50);
		if((ringsens.get_hue() < 10) && (ringsens.get_hue() > 0)) {
			intakeColor = "red";
		} else if((ringsens.get_hue() < 225) && (ringsens.get_hue() > 210)) {
			intakeColor = "blue";
		} else if((ringsens.get_hue() < 90) && (ringsens.get_hue() > 70)) {
			intakeColor = "spurfly";
		} else {
			intakeColor = "neutral";
		}
		pros::delay(10);
	}
}

void colorProbe() {
	static lv_style_t stylering;
	lv_style_init(&stylering);
	lv_style_set_border_width(&stylering, 0);
	lv_style_set_radius(&stylering, 0);
	lv_obj_set_pos(ringind, 345, 3);
	lv_obj_set_size(ringind, 117, 117);
	while(true) {
		if(intakeColor == "red") {
			lv_obj_set_style_bg_color(ringind, lv_color_hex(0xff2a00), LV_PART_MAIN);
			lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0xff2a00), LV_PART_MAIN);
		} else if(intakeColor == "blue") {
			lv_obj_set_style_bg_color(ringind, lv_color_hex(0x0066cc), LV_PART_MAIN);
			lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0x0066cc), LV_PART_MAIN);
		} else if(intakeColor == "spurfly") {
			spurfly = (spurfly + 1) % 360;
			lv_obj_set_style_bg_color(ringind, lv_color_hsv_to_rgb(spurfly, 100, 100), LV_PART_MAIN);
			lv_obj_set_style_bg_color(mainlabel, lv_color_hsv_to_rgb(spurfly, 100, 100), LV_PART_MAIN);
		} else if(intakeColor == "neutral") {
			lv_obj_set_style_bg_color(ringind, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
			lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
		}
		pros::delay(10);
	}
	lv_obj_move_background(ringind);
}
/*void allianceProbe() {
	while(true) {
		if(allianceColor == 'R') {
			pros::screen::set_pen(pros::Color::orange_red);
			pros::screen::print(pros::E_TEXT_MEDIUM, 290, 30, "alliance: red   ");
		} else if(allianceColor == 'B') {
			pros::screen::set_pen(pros::Color::medium_blue);
			pros::screen::print(pros::E_TEXT_MEDIUM, 290, 30, "alliance: blue  ");
		} else if(allianceColor == 'A') {
			pros::screen::set_pen(pros::Color::dark_olive_green);
			pros::screen::print(pros::E_TEXT_MEDIUM, 290, 30, "alliance: driver");
		}
		pros::delay(10);
	}
}*/

// variable changed during auton and driver to determine red/blue/no alliance selection

void redAssign() { allianceColor = 'R'; }

void blueAssign() { allianceColor = 'B'; }

void neutralAssign() { allianceColor = 'A'; }

void discardNormalSet() {
	discardSwitch = false;
	// pros::screen::set_pen(pros::Color::white_smoke);
	// pros::screen::print(pros::E_TEXT_MEDIUM, 310, 60, "normal discard");
}

void discardSafetySet() {
	discardSwitch = true;
	// pros::screen::set_pen(pros::Color::white_smoke);
	// pros::screen::print(pros::E_TEXT_MEDIUM, 310, 60, "safety discard");
}

void discard() {
	if(discardSwitch != true) {
		indexer.set(true);
		pros::delay(2000);
		indexer.set(false);
		return;
	} else if(discardSwitch == true) {
		mogomech.set(false);
		intake.move(-20);
		pros::delay(500);
		intake.move(127);
		pros::delay(500);
		mogomech.set(true);
		intake.move(0);
		neutralAssign();
		return;
	}
}

void ringsensTask() {
	while(true) {
		if((allianceColor == 'R' && intakeColor == "blue") || (allianceColor == 'B' && intakeColor == "red")) {
			discard();
		}
		pros::delay(10);
	}
}