#include "brainui.hpp"
#include "EZ-Template/auton_selector.hpp"
#include "EZ-Template/sdcard.hpp"
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
#include "liblvgl/misc/lv_color.h"
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
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iterator>
#include <string>
#include <vector>
#include "EZ-Template/auton.hpp"


using namespace jas;

std::vector<Auton> jasNAME_SORT = {};
std::vector<std::string>jasDESC_SORT = {};
int j = 0;
int autontable = 0;
int jassize;
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
lv_obj_t * mogoring1 = lv_obj_create(lv_scr_act());
lv_obj_t * mogoring2 = lv_obj_create(lv_scr_act());
lv_obj_t * mogoringback1 = lv_obj_create(lv_scr_act());
lv_obj_t * mogoringback2 = lv_obj_create(lv_scr_act());
lv_obj_t * alliancering = lv_obj_create(lv_scr_act());

    static void jasassign(lv_event_t * e) {
    //for each range- first is equal to the starting value of the range (i.e jasNAME.begin+4 when starting at 4)
    //last is equal one added to the final value of the range (i.e jasNAME.begin+8 when ending at 7) 
    jasNAME_SORT.resize((jas::jasNAME.size()-1));
    jasDESC_SORT.resize((jas::jasNAME.size()-1));
    if((lv_obj_has_state(posneg, LV_STATE_CHECKED)) && (lv_obj_has_state(redblu, LV_STATE_CHECKED))) {
    //bluepos
    jasNAME_SORT.clear();
    jasDESC_SORT.clear();
    jassize = 3;
    std::copy(jas::jasNAME.begin(), jas::jasNAME.begin()+4, jasNAME_SORT.begin());
    std::copy(jas::jasDESC.begin(), jas::jasDESC.begin()+4, jasDESC_SORT.begin());
    } else if ((lv_obj_has_state(posneg, LV_STATE_CHECKED)) && !(lv_obj_has_state(redblu, LV_STATE_CHECKED))){
    //redpos
    jasNAME_SORT.clear();
    jasDESC_SORT.clear();
    jassize = 3;
    std::copy(jas::jasNAME.begin()+4, jas::jasNAME.begin()+8, jasNAME_SORT.begin());
    std::copy(jas::jasDESC.begin()+4, jas::jasDESC.begin()+8, jasDESC_SORT.begin());
    } else if (!(lv_obj_has_state(posneg, LV_STATE_CHECKED)) && (lv_obj_has_state(redblu, LV_STATE_CHECKED))){
    //blueneg
    jasNAME_SORT.clear();
    jasDESC_SORT.clear();
    jassize = 4;
    std::copy(jas::jasNAME.begin()+8, jas::jasNAME.begin()+13, jasNAME_SORT.begin());
    std::copy(jas::jasDESC.begin()+8, jas::jasDESC.begin()+13, jasDESC_SORT.begin());
    } else if (!(lv_obj_has_state(posneg, LV_STATE_CHECKED)) && !(lv_obj_has_state(redblu, LV_STATE_CHECKED))){
    //redneg
    jasNAME_SORT.clear();
    jasDESC_SORT.clear();
    jassize = 4;
    std::copy(jas::jasNAME.begin()+13, jas::jasNAME.begin()+18, jasNAME_SORT.begin());
    std::copy(jas::jasDESC.begin()+13, jas::jasDESC.begin()+18, jasDESC_SORT.begin());
    }
            lv_table_set_cell_value(jauton, 0, 0, ((jasNAME_SORT[j].Name).c_str()));
            lv_table_set_cell_value(jauton, 1, 0, ((jasNAME_SORT[(j+1)].Name).c_str()));
            lv_table_set_cell_value(jauton, 2, 0, ((jasNAME_SORT[(j+2)].Name).c_str()));
            lv_table_set_cell_value(jauton, 3, 0, ((jasNAME_SORT[(j+3)].Name).c_str()));
    }
    static void switches(lv_event_t * e) {
        //positive/negative indicator color set
        if(lv_obj_has_state(posneg, LV_STATE_CHECKED)) {
            lv_obj_set_style_bg_color(posind, lv_color_hex(0xdb8826), LV_PART_MAIN);
            lv_obj_set_style_bg_color(negind, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        } else {
            lv_obj_set_style_bg_color(posind, lv_color_hex(0x5d5d5d), LV_PART_MAIN); 
            lv_obj_set_style_bg_color(negind, lv_color_hex(0x00b5bc), LV_PART_MAIN);
        }
        //red/blue indicator color set
        if(lv_obj_has_state(redblu, LV_STATE_CHECKED)) {
            lv_obj_set_style_bg_color(redbluind, lv_color_hex(0x0066cc), LV_PART_MAIN);
        } else {
            lv_obj_set_style_bg_color(redbluind, lv_color_hex(0xff2a00), LV_PART_MAIN);
        }
    }

    static void updownbtn(lv_event_t * e) {
        if(lv_obj_has_state(autonselectup, LV_EVENT_CLICKED)) {
            if(j == 0 && jassize > 3) {
                j = (jassize) ;
            } else if(j < 4) {
                j = 0;
            } else {
                j = j-4;
            }
        } else if(lv_obj_has_state(autonselectdown, LV_EVENT_CLICKED)) {
            if(j >= jassize) {
                j = 0;
            } else {
            j = ((j+4)%(jassize+1));
            }
        }
            lv_table_set_cell_value(jauton, 0, 0, ((jasNAME_SORT[j].Name).c_str()));
            lv_table_set_cell_value(jauton, 1, 0, ((jasNAME_SORT[(j+1)].Name).c_str()));
            lv_table_set_cell_value(jauton, 2, 0, ((jasNAME_SORT[(j+2)].Name).c_str()));
            lv_table_set_cell_value(jauton, 3, 0, ((jasNAME_SORT[(j+3)].Name).c_str()));
        //theres a small issue where if you are on the last page of the table, and then switch to a different filter with a 
        //lower number of pages, it doesnt select the auton of any of them (displaying the no auton selected text) until
        //the user switches back to the other filter, and then back again. gonna fix this after comp
    }

    static void selectauton(lv_event_t * e) {
        uint16_t row, col;
        lv_table_get_selected_cell(jauton, &row, &col);
        if((row == 1) && (j+1 > jassize)) {lv_label_set_text(selectedAuton, "No auton selected");}
        else if((row == 2) && (j+2 > jassize)) {lv_label_set_text(selectedAuton, "No auton selected");}
        else if((row == 3) && (j+3 > jassize)) {lv_label_set_text(selectedAuton, "No auton selected");}
        else if (strcmp((jasDESC_SORT[autontable]).c_str() , "") == 0){lv_label_set_text(selectedAuton, "No auton selected");}
        else if(row == 0) {lv_label_set_text(selectedAuton, ((jasDESC_SORT[j]).c_str())), autontable = j;}
        else if(row == 1) {lv_label_set_text(selectedAuton, ((jasDESC_SORT[(j+1)]).c_str())), autontable = j+1;}
        else if(row == 2) {lv_label_set_text(selectedAuton, ((jasDESC_SORT[(j+2)]).c_str())), autontable = j+2;}
        else if(row == 3) {lv_label_set_text(selectedAuton, ((jasDESC_SORT[(j+3)]).c_str())), autontable = j+3;}
        else {lv_label_set_text(selectedAuton, "No auton selected");}
    }
    static void jasautonselector(lv_event_t * e) {
        //this is a big if tree that allows the user to manually set the visuals associated with each auton.
        //in each if statement, set the string to be the corresponding string in your auton description
    if (strcmp((jasDESC_SORT[autontable]).c_str() , "blue 50% wp") == 0) {
        as::auton_selector.auton_page_current = 0;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0x0066cc), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 23);
        lv_obj_set_pos(mogoring1, 260, 200);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "at-home testing for \nblue auton") == 0) {
        as::auton_selector.auton_page_current = 1;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 73);
        lv_obj_set_pos(mogoring1, 260, 150);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "Move forward") == 0) {
        as::auton_selector.auton_page_current = 2;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 73);
        lv_obj_set_pos(mogoring1, 260, 150);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
    }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "skills") == 0) {
        as::auton_selector.auton_page_current = 3;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0xff2a00), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 73);
        lv_obj_set_pos(mogoring1, 260, 150);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0xff2a00), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0xff2a00), LV_PART_MAIN);
        lv_obj_set_style_bg_color(redbluind, lv_color_hex(0xff2a00), LV_PART_MAIN);
    }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "red 50% wp") == 0) {
        as::auton_selector.auton_page_current = 4;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0xff2a00), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 23);
        lv_obj_set_pos(mogoring1, 260, 200);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "at-home testing for \nred auton") == 0) {
        as::auton_selector.auton_page_current = 5;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 73);
        lv_obj_set_pos(mogoring1, 260, 150);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "blue 4 ring no WP") == 0) {
        as::auton_selector.auton_page_current = 6;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0x0066cc), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 48);
        lv_obj_set_pos(mogoring1, 260, 175);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "blue 4 ring wp \n(DO NOT RUN)") == 0) {
        as::auton_selector.auton_page_current = 7;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0x0066cc), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 35);
        lv_obj_set_pos(mogoring1, 260, 188);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x0066cc), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "blue 6 ring no WP") == 0) {
        as::auton_selector.auton_page_current = 8;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0x0066cc), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 73);
        lv_obj_set_pos(mogoring1, 260, 150);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "red 4 ring no WP") == 0) {
        as::auton_selector.auton_page_current = 9;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0xff2a00), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 48);
        lv_obj_set_pos(mogoring1, 260, 175);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "red 4 ring wp \n(DO NOT RUN)") == 0) {
        as::auton_selector.auton_page_current = 10;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0xff2a00), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 35);
        lv_obj_set_pos(mogoring1, 260, 188);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0xff2a00), LV_PART_MAIN);
        }
    else if (strcmp((jasDESC_SORT[autontable]).c_str() , "red 6 ring no WP") == 0) {
        as::auton_selector.auton_page_current = 11;
        lv_obj_set_style_bg_color(mogoring1, lv_color_hex(0xff2a00), LV_PART_MAIN);
        lv_obj_set_size(mogoring1, 46, 73);
        lv_obj_set_pos(mogoring1, 260, 150);
        lv_obj_set_style_bg_color(mogoring2, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_pos(mogoring2, 340, 150);
        lv_obj_set_style_bg_color(alliancering, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
        }
    //pros::delay(500); //<----v only uncomment these if testing on the brain, it runs auto immediately after it is selected
    //autonomous(); //<--------^
}

lv_event_cb_t autonpage = updownbtn;
lv_event_cb_t rbpnswitches = switches;
lv_event_cb_t autontouch = selectauton;
lv_event_cb_t autonsort = jasassign;
lv_event_cb_t autonassignment = jasautonselector;


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

        static lv_style_t styleind;
    lv_style_init(&styleind);
    lv_style_set_border_width(&styleind, 0);
    lv_style_set_radius(&styleind, 0);
    lv_style_set_bg_color(&styleind, lv_color_hex(0x5d5d5d));

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
        lv_obj_set_size(mogoring1, 46, 73);
        lv_obj_set_size(mogoring2, 46, 73);
        lv_obj_set_size(mogoringback1, 46, 73);
        lv_obj_set_size(mogoringback2, 46, 73);
        lv_obj_set_size(alliancering, 66, 14);
            lv_obj_set_pos(mogoring1, 260, 150);
            lv_obj_set_pos(mogoring2, 340, 150);
            lv_obj_set_pos(mogoringback1, 260, 150);
            lv_obj_set_pos(mogoringback2, 340, 150);
            lv_obj_set_pos(alliancering, 267, 72);
    lv_obj_move_background(mogoringback1);
    lv_obj_move_background(mogoringback2);
                lv_obj_add_style(mogoring1, &styleind, LV_PART_MAIN);
                lv_obj_add_style(mogoring2, &styleind, LV_PART_MAIN);
                lv_obj_add_style(mogoringback1, &styleind, LV_PART_MAIN);
                lv_obj_add_style(mogoringback2, &styleind, LV_PART_MAIN);
                lv_obj_add_style(alliancering, &styleind, LV_PART_MAIN);
                lv_obj_set_scrollbar_mode(alliancering, LV_SCROLLBAR_MODE_OFF);
                lv_obj_set_style_pad_top(jauton, 8, LV_PART_ITEMS);
                lv_obj_set_style_pad_bottom(jauton, 6, LV_PART_ITEMS);
                lv_obj_set_style_pad_left(jauton, 4, LV_PART_ITEMS);
                lv_obj_add_style(jauton, &style, LV_PART_MAIN);
                lv_obj_add_style(jauton, &style, LV_PART_ITEMS);
        lv_table_set_col_width(jauton, 0, 230);
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
                lv_obj_add_style(negind, &styleind, LV_PART_MAIN);
        lv_obj_set_size(posind, 66, 66);
            lv_obj_set_pos(posind, 412, 126);
                lv_obj_add_style(posind, &styleind, LV_PART_MAIN);
        lv_obj_set_size(redbluind, 62, 79);
            lv_obj_set_pos(redbluind, 266, 22);
                lv_obj_add_style(redbluind, &styleind, LV_PART_MAIN);
            lv_obj_set_pos(autondesc, 7, 45);
                lv_obj_add_style(autondesc, &style, LV_PART_MAIN);
                    lv_obj_add_event_cb(posneg, autonsort, LV_EVENT_ALL, NULL);
                    lv_obj_add_event_cb(redblu, autonsort, LV_EVENT_ALL, NULL);
                    lv_obj_add_event_cb(autonselectup, autonpage, LV_EVENT_CLICKED, NULL);
                    lv_obj_add_event_cb(autonselectdown, autonpage, LV_EVENT_CLICKED, NULL);
                    lv_obj_add_event_cb(jauton, switches, LV_EVENT_VALUE_CHANGED, NULL);
                    lv_obj_add_event_cb(jauton, autontouch, LV_EVENT_VALUE_CHANGED,NULL);
                    lv_obj_add_event_cb(jauton, autonassignment, LV_EVENT_VALUE_CHANGED,NULL);
            lv_label_set_text(autondesc, "auton selection:");
}