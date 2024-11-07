#include "brainui.hpp"
#include "EZ-Template/auton.hpp"
#include "EZ-Template/util.hpp"
#include "liblvgl/core/lv_disp.h"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/core/lv_obj_scroll.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/extra/widgets/list/lv_list.h"
#include "liblvgl/lv_api_map.h"
#include "liblvgl/lv_conf_internal.h"
#include "liblvgl/misc/lv_style.h"
#include "liblvgl/widgets/lv_btn.h"
#include "liblvgl/widgets/lv_img.h"
#include "liblvgl/widgets/lv_label.h"
#include "liblvgl/widgets/lv_roller.h"
#include "liblvgl/widgets/lv_switch.h"
#include "liblvgl/lvgl.h"
#include "liblvgl/widgets/lv_table.h"
#include "main.h"
#include "pros/rtos.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include "subsystems_auton.hpp"
#include "EZ-Template/auton.hpp"
#include "EZ-Template/auton_selector.hpp"

std::vector<std::string> jasDESC = {
      "at-home testing for \nred auton",
      "at-home testing for \nblue auton",
      "red 6 ring no WP",
      "blue 6 ring no WP",
      "red 4 ring wp \n(DO NOT RUN)",  
      "blue 4 ring wp \n(DO NOT RUN)",
      "red 50% wp",
      "blue 50% wp",
      "red 4 ring no WP",
      "blue 4 ring no WP",
      "Move forward",
      "skills"
      };

std::vector<Auton> jasNAME = {
      Auton("testautonRed", testautonRed),
      Auton("testautonBlue", testautonBlue),
      Auton("red_6ring", red_6ring),
      Auton("blue_6ring", blue_6ring),
      Auton("red_4ring", red_4ring),      
      Auton("blue_4ring", blue_4ring),
      Auton("red_50WP", red_50WP),
      Auton("blue_50WP", blue_50WP),
      Auton("red_4greed", red_4greed),
      Auton("blue_4greed", blue_4greed),
      Auton("move_forward", move_forward),
      Auton("skills", skills),
      };

int j = 0;

lv_obj_t * overlay = lv_img_create(lv_scr_act());
LV_IMG_DECLARE(brainuioverlay);
lv_obj_t * autonselectup = lv_btn_create(lv_scr_act());
lv_obj_t * autonselectdown = lv_btn_create(lv_scr_act());
lv_obj_t * redblu = lv_switch_create(lv_scr_act());
lv_obj_t * posneg = lv_switch_create(lv_scr_act());
lv_obj_t * negind = lv_obj_create(lv_scr_act());
lv_obj_t * posind = lv_obj_create(lv_scr_act());
lv_obj_t * redbluind = lv_obj_create(lv_scr_act());
lv_obj_t * jauton = lv_table_create(lv_scr_act());
lv_obj_t * selectedAuton = lv_label_create(lv_scr_act());
lv_obj_t * selectedAutonbox = lv_obj_create(lv_scr_act());
lv_obj_t * autondesc = lv_label_create(lv_scr_act());

    static void jasassign(lv_event_t * e) {
    //fix this, this assigns autons to the vector. right now it is doing that but its not erasing the old, and its being funny
    //also the vector isnt being cleared properly or something and its giving a prefetch error
    lv_obj_has_state(posneg, LV_STATE_CHECKED) ? (lv_obj_has_state(redblu, LV_STATE_CHECKED) ? 
    jasNAME.clear(), jasDESC.clear(),
    jasNAME.push_back(Auton("blue_50WP", blue_50WP)),
    jasNAME.push_back(Auton("testautonBlue", testautonBlue)),
    jasNAME.push_back(Auton("move_forward", move_forward)),

    jasDESC.push_back("blue 50% wp"),
    jasDESC.push_back("at-home testing for \nblue auton"),
    jasDESC.push_back("move_forward")
    : 
    jasNAME.clear(), jasDESC.clear(),
    jasNAME.push_back(Auton("red_50WP", red_50WP)),
    jasNAME.push_back(Auton("testautonRed", testautonRed)),
    jasNAME.push_back(Auton("move_forward", move_forward)),

    jasDESC.push_back("red 50% wp"),
    jasDESC.push_back("at-home testing for \nred auton"),
    jasDESC.push_back("move_forward")
    ):
    (lv_obj_has_state(redblu, LV_STATE_CHECKED) ? 
    jasNAME.clear(), jasDESC.clear(),
    jasNAME.push_back(Auton("testautonBlue", testautonBlue)),
    jasNAME.push_back(Auton("move_forward", move_forward)),
    
    jasDESC.push_back("at-home testing for \nblue auton"),
    jasDESC.push_back("move_forward")
    : 
    jasNAME.clear(), jasDESC.clear(),
    jasDESC.push_back("at-home testing for \nred auton"),
    jasDESC.push_back("move_forward")
    );
    //jasNAME.shrink_to_fit(), jasDESC.shrink_to_fit();
        j = 0;
        lv_table_set_cell_value(jauton, 0, 0, ((jasNAME[j].Name).c_str()));
        lv_table_set_cell_value(jauton, 1, 0, ((jasNAME[j+1].Name).c_str()));
        lv_table_set_cell_value(jauton, 2, 0, ((jasNAME[j+2].Name).c_str()));
        lv_table_set_cell_value(jauton, 3, 0, ((jasNAME[j+3].Name).c_str()));
    }
    static void switches(lv_event_t * e) {
        if(lv_obj_has_state(posneg, LV_STATE_CHECKED)) {
            lv_obj_set_style_bg_color(posind, lv_color_hex(0xdb8826), LV_PART_MAIN);
            lv_obj_set_style_bg_color(negind, lv_color_hex(0x15171a), LV_PART_MAIN);
        } else {
            lv_obj_set_style_bg_color(posind, lv_color_hex(0x15171a), LV_PART_MAIN); 
            lv_obj_set_style_bg_color(negind, lv_color_hex(0x00b5bc), LV_PART_MAIN);
        }

        if(lv_obj_has_state(redblu, LV_STATE_CHECKED)) {
            lv_obj_set_style_bg_color(redbluind, lv_color_hex(0x0066cc), LV_PART_MAIN);
        } else {
            lv_obj_set_style_bg_color(redbluind, lv_color_hex(0xff2a00), LV_PART_MAIN);
        }
    }

    static void updownbtn(lv_event_t * e) {
        if(lv_obj_has_state(autonselectup, LV_EVENT_CLICKED)) {
            j == 0 ? j = jasNAME.size()-4: (j > 4 ? j = (j-4)%jasNAME.size() : j = 0);
        } else if(lv_obj_has_state(autonselectdown, LV_EVENT_CLICKED)) {
            j = (j+4)%jasNAME.size();
        }   lv_table_set_cell_value(jauton, 0, 0, ((jasNAME[j].Name).c_str()));
            lv_table_set_cell_value(jauton, 1, 0, ((jasNAME[j+1].Name).c_str()));
            lv_table_set_cell_value(jauton, 2, 0, ((jasNAME[j+2].Name).c_str()));
            lv_table_set_cell_value(jauton, 3, 0, ((jasNAME[j+3].Name).c_str()));

    }

    static void selectauton(lv_event_t * e) {
        uint16_t row, col;
        lv_table_get_selected_cell(jauton, &row, &col);
        row == 0 ? lv_label_set_text(selectedAuton, ((jasDESC[j]).c_str())) :
        row == 1 ? lv_label_set_text(selectedAuton, ((jasDESC[j+1]).c_str())) :
        row == 2 ? lv_label_set_text(selectedAuton, ((jasDESC[j+2]).c_str())) :
        row == 3 ? lv_label_set_text(selectedAuton, ((jasDESC[j+3]).c_str())) :
        lv_label_set_text(selectedAuton, "No auton selected");
    }

lv_event_cb_t autonpage = updownbtn;
lv_event_cb_t rbpnswitches = switches;
lv_event_cb_t autontouch = selectauton;
lv_event_cb_t autonsort = jasassign;



void screeninit(){
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_border_width(&style, 0);
    lv_style_set_radius(&style, 0);
    lv_style_set_text_color(&style, lv_color_hex(0xe3c5ff));
    lv_style_set_bg_color(&style, lv_color_hex(0x100718));

    static lv_style_t stylebtn;
    lv_style_init(&stylebtn);
    lv_style_set_border_width(&stylebtn, 2);
    lv_style_set_radius(&stylebtn, 6);
    lv_style_set_border_color(&stylebtn, lv_color_hex(0x100718));
    lv_style_set_bg_color(&stylebtn, lv_color_hex(0xe3c5ff));

    pros::screen::set_pen(0xe3c5ff);
    pros::screen::set_eraser(0x15171a); 
        lv_img_set_src(overlay, &brainuioverlay);
        lv_obj_move_foreground(overlay);
        lv_obj_set_size(autonselectup, 11, 58);
        lv_obj_set_pos(autonselectup, 242, 50);
        lv_obj_add_style(autonselectup, &stylebtn, LV_PART_MAIN);
        lv_obj_add_style(autonselectdown, &stylebtn, LV_PART_MAIN);
        lv_obj_set_style_bg_color(autonselectup, lv_color_hex(0xe3c5ff), LV_PART_MAIN);
        lv_obj_set_size(autonselectdown, 11, 58);
        lv_obj_set_pos(autonselectdown, 242, 118);
            lv_obj_set_style_pad_top(jauton, 8, LV_PART_ITEMS);
            lv_obj_set_style_pad_bottom(jauton, 6, LV_PART_ITEMS);
            lv_obj_set_style_pad_left(jauton, 4, LV_PART_ITEMS);
            lv_obj_add_style(jauton, &style, LV_PART_MAIN);
            lv_obj_add_style(jauton, &style, LV_PART_ITEMS);
            lv_table_set_col_width(jauton, 0, 230);
            lv_table_set_cell_value(jauton, 0, 0, ((jasNAME[j].Name).c_str()));
            lv_table_set_cell_value(jauton, 1, 0, ((jasNAME[j+1].Name).c_str()));
            lv_table_set_cell_value(jauton, 2, 0, ((jasNAME[j+2].Name).c_str()));
            lv_table_set_cell_value(jauton, 3, 0, ((jasNAME[j+3].Name).c_str()));
            lv_obj_move_background(jauton);
                //add selected auton code here (label)
                lv_obj_add_style(selectedAuton, &style, LV_PART_MAIN);
                lv_obj_set_pos(selectedAuton, 5, 182);
                lv_obj_set_size(selectedAuton, 230, 47);
                lv_obj_add_style(selectedAutonbox, &style, LV_PART_MAIN);
                lv_obj_set_size(selectedAutonbox, 230, 230);
                lv_obj_set_pos(selectedAutonbox, 5, 5);
                lv_obj_move_background(selectedAutonbox);
                lv_obj_set_style_pad_left(selectedAuton, 4, LV_PART_MAIN);
                lv_obj_set_style_pad_top(selectedAuton, 8, LV_PART_MAIN);
                lv_label_set_text(selectedAuton, "No auton selected");
        lv_obj_set_size(jauton, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_pos(jauton, 5, 60);
        lv_obj_move_foreground(autonselectup);
        lv_obj_move_foreground(autonselectdown);
        lv_obj_set_style_bg_color(autonselectdown, lv_color_hex(0xe3c5ff), LV_PART_MAIN);
        lv_obj_set_style_bg_color(redblu, lv_color_hex(0xff2a00), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(redblu, lv_color_hex(0x0066cc), LV_STATE_CHECKED | LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(redblu, lv_color_hex(0xe3c5ff), LV_PART_KNOB);
        lv_obj_set_size(redblu, 42, 20);
        lv_obj_set_pos(redblu, 41, 10);
        lv_obj_set_style_bg_color(posneg, lv_color_hex(0x00b5bc), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(posneg, lv_color_hex(0xdb8826), LV_STATE_CHECKED | LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(posneg, lv_color_hex(0xe3c5ff), LV_PART_KNOB);
        lv_obj_set_size(posneg, 42, 20);
        lv_obj_set_pos(posneg, 156, 10);
        lv_obj_set_size(negind, 66, 30);
        lv_obj_set_pos(negind, 412, 197);
        lv_obj_set_scrollbar_mode(negind, LV_SCROLLBAR_MODE_OFF);
        lv_obj_add_style(negind, &style, LV_PART_MAIN);
        lv_obj_set_size(posind, 66, 66);
        lv_obj_set_pos(posind, 412, 126);
        lv_obj_add_style(posind, &style, LV_PART_MAIN);
        lv_obj_set_size(redbluind, 62, 79);
        lv_obj_set_pos(redbluind, 266, 22);
        lv_obj_add_style(redbluind, &style, LV_PART_MAIN);
        lv_obj_add_event_cb(posneg, switches, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(redblu, switches, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(posneg, autonsort, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(redblu, autonsort, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(autonselectup, autonpage, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(autonselectdown, autonpage, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(jauton, autontouch, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_style(autondesc, &style, LV_PART_MAIN);
    lv_obj_set_pos(autondesc, 7, 45);
    lv_label_set_text(autondesc, "auton descriptions:");
}


