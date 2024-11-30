#include "main.h"
//somewhere in here is a prefetch error. i am too tired for this

//use iterator to create label objects, and to set some variable or something for each of them to track a motor
//for the hue thing, use hsv and set the hue to whatever color (probably green for this, pink for ez) and the value to like temperature * 2 or something idk. maybe temperature * 2 then - 30 or something bc we dont want it to light up when its cold idk
vector<int8_t> motorportsbar {};

vector<pros::Motor> motors {
    pros::Motor intake1(4);
};

pros::MotorGroup motorports({motorportsbar});

lv_obj_t * skibidi = lv_table_create(motortemps);
lv_obj_t * motorview;
int sigma = 0;

static void gettemp(lv_event_t * e) {
    const char *getmotor = (char*)lv_event_get_user_data(e); //do stuff here im not really sure what but somehow pull the motor value from the user data and use it for get temperature or something
    motorports[*getmotor].get_temperature
    
    printf("Motor: %d", *getmotor);
    sigma += 1;
    lv_table_set_cell_value_fmt(skibidi, 0, 0, "ohio %d %d", *getmotor, sigma);
}

lv_event_cb_t getTemp = gettemp;

void tempcheck() {
            static lv_style_t stylemotor;
            lv_style_init(&stylemotor);
            lv_style_set_border_color(&stylemotor, lv_color_hex(0xcfffe9));
            lv_style_set_border_width(&stylemotor, 2);
            lv_style_set_radius(&stylemotor, 8);
            lv_style_set_text_color(&stylemotor, lv_color_hex(0x071808));
            lv_style_set_bg_color(&stylemotor, lv_color_hex(0xcfffe9));
            lv_style_set_bg_opa(&stylemotor, 255);
            lv_style_set_text_font(&stylemotor, &pros_font_dejavu_mono_18);
            lv_style_set_text_align(&stylemotor, LV_TEXT_ALIGN_CENTER);
            lv_style_set_pad_all(&stylemotor, 6);


    for(int a = 1; a < 22; a++) {
        int device = pros::c::get_plugged_type(a);
        printf("device plugged type: {plugged type: %d}\n", device);
        if(device == 0) motorportsbar.push_back(a);
    } 
    int motorrow = 0;
    for(int b = 0; b < motorportsbar.size(); b++){
        motorview = lv_label_create(motortemps);
        lv_obj_add_style(motorview, &stylemotor, LV_PART_MAIN);
        lv_obj_set_size(motorview, 97, 39);
        lv_label_set_long_mode(motorview, LV_LABEL_LONG_SCROLL);
        if(b != 0 && b%4 == 0) motorrow++;
        lv_obj_set_pos(motorview, (17+b%4*116), (68+motorrow*58));
        lv_label_set_text_fmt(motorview, "Motor %d", motorportsbar[b]);
        lv_obj_add_event_cb(motorview, getTemp, LV_EVENT_ALL, &motorportsbar[b]);
    }
    printf("motor port count: {port count: %d}\n", motorportsbar.size());
    printf("motor port: {port number: %hhd}\n", motorportsbar[0]);
}