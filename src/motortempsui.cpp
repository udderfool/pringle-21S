#include "main.h"

using namespace jas;

/* void motorspopulate::motorpopulate(std::vector<motors::motordata> motors) {
 motortable = {};
 motortable.assign(motors.begin(), motors.end());
}*/
// list of motors to get temperature

float driveTemp;
float intakeTemp;
float wallmechTemp;

vector<lv_obj_t *> motorboxes{};

lv_obj_t *motorview;
lv_obj_t *mainlabel = lv_label_create(motortemps);

static void gettemp(lv_event_t *e) {
	lv_obj_t *target = lv_event_get_target(e);
	const char *getmotor = (char *)lv_event_get_user_data(e);
	double temp = motorbar[*getmotor].motor.get_temperature();

	lv_obj_set_style_bg_opa(target, (temp - 30) * 5, LV_PART_MAIN);
	printf("Temperature: %f \n", temp);
	printf("Motor: %d \n", *getmotor);
}

lv_event_cb_t getTemp = gettemp;

void tempcheck() {
	// motorbar.assign(Motors.motortable.begin(), Motors.motortable.end());
	static lv_style_t stylemotor;
	lv_style_init(&stylemotor);
	lv_style_set_border_color(&stylemotor, lv_color_hex(0xcfffe9));
	lv_style_set_border_width(&stylemotor, 2);
	lv_style_set_radius(&stylemotor, 8);
	lv_style_set_text_color(&stylemotor, lv_color_hex(0x071808));
	lv_style_set_bg_color(&stylemotor, lv_color_hex(0xcfffe9));
	lv_style_set_bg_opa(&stylemotor, 0);
	lv_style_set_text_font(&stylemotor, &pros_font_dejavu_mono_18);
	lv_style_set_text_align(&stylemotor, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_ver(&stylemotor, 6);
	int motorrow = 0;
	char vectorprobe = 0;
	for(int b = 0; b < motorbar.size(); b++) {
		motorview = lv_label_create(motortemps);
		lv_obj_add_style(motorview, &stylemotor, LV_PART_MAIN);
		lv_obj_set_size(motorview, 97, 39);
		lv_label_set_long_mode(motorview, LV_LABEL_LONG_SCROLL);
		lv_label_set_text_fmt(motorview, "%s", motorbar[b].name.c_str());
		lv_obj_add_event_cb(motorview, getTemp, LV_EVENT_REFRESH, &motorbar[b].index);
		if(b != 0 && b % 4 == 0) motorrow++;
		lv_obj_set_pos(motorview, (17 + b % 4 * 116), (68 + motorrow * 58));
		motorboxes.push_back(motorview);
	}
	lv_obj_add_style(mainlabel, &stylemotor, LV_PART_MAIN);
	// lv_obj_set_style_border_color(mainlabel, lv_color_hex(0x071808),
	// LV_PART_MAIN);
	lv_obj_set_style_pad_all(mainlabel, 6, LV_PART_MAIN);
	lv_obj_set_style_text_color(mainlabel, lv_color_hex(0xcfffe9), LV_PART_MAIN);
	lv_obj_set_style_text_font(mainlabel, &lv_font_montserrat_36, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(mainlabel, 255, LV_PART_MAIN);
	lv_obj_align(mainlabel, LV_ALIGN_TOP_MID, 0, 6);
	lv_label_set_text(mainlabel, "Motor Temperatures");
	// printf("motor port count: {port count: %d}\n", motorbar.size());
}

void tempcheckctrl() {
	while(true) {
		driveTemp = (motorbar[1].motor.get_temperature() + motorbar[2].motor.get_temperature() + motorbar[3].motor.get_temperature() +
					 motorbar[5].motor.get_temperature() + motorbar[6].motor.get_temperature() + motorbar[7].motor.get_temperature()) /
					6;
		intakeTemp = (motorbar[0].motor.get_temperature() + motorbar[4].motor.get_temperature()) / 2;
		wallmechTemp = motorbar[8].motor.get_temperature();

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) == true) {
			if(intakeTemp <= 30)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "i: cool, %.0f°C    ", intakeTemp);
			else if(intakeTemp > 30 && intakeTemp <= 45)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "i: warm, %.0f°C    ", intakeTemp);
			else if(intakeTemp > 45)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "i: hot, %.0f°C    ", intakeTemp);
			pros::delay(90);
		} else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) == true) {
			if(wallmechTemp <= 30)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "w: cool, %.0f°C    ", wallmechTemp);
			else if(wallmechTemp > 30 && wallmechTemp <= 45)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "w: warm, %.0f°C    ", wallmechTemp);
			else if(wallmechTemp > 45)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "w: hot, %.0f°C    ", wallmechTemp);
			pros::delay(90);
		} else {
			if(driveTemp <= 30)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "d: cool, %.0f°C    ", driveTemp);
			else if(driveTemp > 30 && driveTemp <= 45)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "d: warm, %.0f°C    ", driveTemp);
			else if(driveTemp > 45)
				pros::c::controller_print(pros::E_CONTROLLER_MASTER, 0, 0, "d: hot, %.0f°C    ", driveTemp);
			pros::delay(90);
		}
		pros::delay(10);
	}
}