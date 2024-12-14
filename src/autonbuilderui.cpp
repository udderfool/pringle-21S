#include "brainui.hpp"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/core/lv_obj_scroll.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/lv_api_map.h"
#include "liblvgl/misc/lv_style.h"
#include "liblvgl/widgets/lv_img.h"
#include "main.h"

int mogo1;
int mogo2;
int redblubuilder(1);
int posnegbuilder(3);
int goalrushbuilder(5);
bool allianceringbuilder(true);
int * rings;

lv_obj_t *builderoverlay;
lv_obj_t *Mogo1;
lv_obj_t *Mogo1back;
lv_obj_t *Mogo2;
lv_obj_t *Mogo2back;
lv_obj_t *Pos;
lv_obj_t *Neg;
lv_obj_t *RedBlu;
lv_obj_t *AllianceRing;
lv_obj_t *GoalRush;

LV_IMG_DECLARE(autonbuilderoverlay);

static void mogopress(lv_event_t * e) {
    lv_obj_t *target = lv_event_get_target(e);
    target == Mogo1 || target == Mogo1back ? rings = &mogo1 : rings = &mogo2;
    *rings = (*rings+1)%7;
    lv_obj_set_size(Mogo1, 67, 108-(18*mogo1));
    lv_obj_set_size(Mogo2, 67, 108-(18*mogo2));
}

static void specify(lv_event_t * e) {
    lv_obj_t *target = lv_event_get_target(e);

    if(target == RedBlu) redblubuilder == 0 ? redblubuilder = 1 : redblubuilder = 0;
    if(target == AllianceRing) allianceringbuilder == false ? allianceringbuilder = true : allianceringbuilder = false;
    if(target == GoalRush && posnegbuilder == 4) {
        goalrushbuilder == 5 ? goalrushbuilder = 6 : goalrushbuilder = 5;
    } 

    if(target == Pos) {
        posnegbuilder = 4;
        lv_obj_set_style_bg_color(Neg, colortable[5], LV_PART_MAIN);
        lv_obj_set_style_bg_color(Pos, colortable[posnegbuilder], LV_PART_MAIN);
        lv_obj_set_style_bg_opa(GoalRush, 255, LV_PART_MAIN);
    }
    if (target == Neg) {
        posnegbuilder = 3; 
        lv_obj_set_style_bg_color(Pos, colortable[5], LV_PART_MAIN);
        lv_obj_set_style_bg_color(Neg, colortable[posnegbuilder], LV_PART_MAIN);
        lv_obj_set_style_bg_opa(GoalRush, 0, LV_PART_MAIN);
        goalrushbuilder = 5;
    }

    lv_obj_set_style_bg_color(RedBlu, colortable[redblubuilder], LV_PART_MAIN);
    lv_obj_set_style_bg_color(Mogo1back, colortable[redblubuilder], LV_PART_MAIN);
    lv_obj_set_style_bg_color(Mogo2back, colortable[redblubuilder], LV_PART_MAIN);
    lv_obj_set_style_bg_color(GoalRush, colortable[goalrushbuilder], LV_PART_MAIN);
    allianceringbuilder == false ? lv_obj_set_style_bg_opa(AllianceRing, 5, LV_PART_MAIN) : lv_obj_set_style_bg_opa(AllianceRing, 255, LV_PART_MAIN);
}

lv_event_cb_t mogoPress = mogopress;
lv_event_cb_t Specify = specify;

void autonbuilderinit() {
    builderoverlay = lv_img_create(autobuilder);
    Mogo1 = lv_btn_create(autobuilder);
    Mogo1back = lv_btn_create(autobuilder);
    Mogo2 = lv_btn_create(autobuilder);
    Mogo2back = lv_btn_create(autobuilder);
    Pos = lv_btn_create(autobuilder);
    Neg = lv_btn_create(autobuilder);
    RedBlu = lv_btn_create(autobuilder);
    AllianceRing = lv_btn_create(autobuilder);
    GoalRush = lv_btn_create(autobuilder);

    static lv_style_t styleindbuilder;
	lv_style_init(&styleindbuilder);
	lv_style_set_border_width(&styleindbuilder, 0);
	lv_style_set_radius(&styleindbuilder, 0);
	lv_style_set_bg_color(&styleindbuilder, lv_color_hex(0x5d5d5d));
    //lv_style_set_shadow_opa(&styleindbuilder, 0);
    
    lv_img_set_src(builderoverlay, &autonbuilderoverlay);

    lv_obj_set_pos(Mogo1, 49, 90);
    lv_obj_set_pos(Mogo1back, 49, 90);
    lv_obj_set_pos(Mogo2, 364, 90);
    lv_obj_set_pos(Mogo2back, 364, 90);
    lv_obj_set_pos(Pos, 142, 69);
    lv_obj_set_pos(Neg, 290, 88);
    lv_obj_set_pos(RedBlu, 204, 13);
    lv_obj_set_pos(AllianceRing, 204, 59);
    lv_obj_set_pos(GoalRush, 216, 153);

    lv_obj_set_size(Mogo1, 67, 105);
    lv_obj_set_size(Mogo1back, 67, 105);
    lv_obj_set_size(Mogo2, 67, 105);
    lv_obj_set_size(Mogo2back, 67, 105);
    lv_obj_set_size(Pos, 48, 48);
    lv_obj_set_size(Neg, 48, 11);
    lv_obj_set_size(RedBlu, 72, 74);
    lv_obj_set_size(AllianceRing, 72, 17);
    lv_obj_set_size(GoalRush, 48, 73);

    lv_obj_add_style(Mogo1, &styleindbuilder, LV_PART_MAIN);
    lv_obj_add_style(Mogo1back, &styleindbuilder, LV_PART_MAIN);
    lv_obj_add_style(Mogo2, &styleindbuilder, LV_PART_MAIN);
    lv_obj_add_style(Mogo2back, &styleindbuilder, LV_PART_MAIN);
    lv_obj_add_style(Pos, &styleindbuilder, LV_PART_MAIN);
    lv_obj_add_style(Neg, &styleindbuilder, LV_PART_MAIN);
    lv_obj_add_style(RedBlu, &styleindbuilder, LV_PART_MAIN);
    lv_obj_add_style(AllianceRing, &styleindbuilder, LV_PART_MAIN);
    lv_obj_add_style(GoalRush, &styleindbuilder, LV_PART_MAIN);

    lv_obj_move_background(Mogo1back);
    lv_obj_move_background(Mogo2back);

    lv_obj_add_event_cb(Mogo1, mogoPress, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Mogo1back, mogoPress, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Mogo2, mogoPress, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Mogo2back, mogoPress, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Pos, Specify, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Neg, Specify, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(RedBlu, Specify, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(AllianceRing, Specify, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(GoalRush, Specify, LV_EVENT_CLICKED, NULL);

    lv_obj_move_foreground(Mogo1);
    lv_obj_move_foreground(Mogo2);
    lv_obj_move_foreground(AllianceRing);
    lv_obj_move_foreground(builderoverlay);

    lv_event_send(RedBlu, LV_EVENT_CLICKED, NULL);
    lv_event_send(Neg, LV_EVENT_CLICKED, NULL);
    lv_event_send(AllianceRing, LV_EVENT_CLICKED, NULL);
}