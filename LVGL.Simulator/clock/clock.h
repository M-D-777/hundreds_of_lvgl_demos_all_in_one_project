#ifndef CLOCK_H
#define CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif
#include <Windows.h>

#include "../lvgl/lvgl.h"

LV_IMG_DECLARE(hand_h);
LV_IMG_DECLARE(hand_m);
LV_IMG_DECLARE(hand_s);

LV_IMG_DECLARE(star_bg);

#if LIYUE_VER
LV_IMG_DECLARE(star_mask_liyue);
LV_IMG_DECLARE(daytime);
LV_IMG_DECLARE(moonrise);
LV_IMG_DECLARE(sunrise);
LV_IMG_DECLARE(sunset);
#else
LV_IMG_DECLARE(star_mask);
#endif

LV_IMG_DECLARE(Horoscope03);
LV_IMG_DECLARE(Horoscope04);
LV_IMG_DECLARE(Horoscope05);
LV_IMG_DECLARE(Horoscope06);
LV_IMG_DECLARE(arc_mask);

//定义时分秒指针图像对象
static lv_obj_t* lvMinute;
static lv_obj_t* lvHour;
static lv_obj_t* lvSecond;
static lv_obj_t* arc;
static lv_style_t arc_style;
static lv_anim_t anim_center_gear;
static lv_anim_t anim_left_btm_gear;
static lv_anim_t anim_right_top_gear;
static lv_anim_t anim_right_btm_gear;

static lv_anim_t anim_hand_h;
static lv_anim_t anim_hand_m;
static lv_anim_t anim_hand_s;

static lv_timer_t* clock_timer;

static void rotate_img(void* img, int32_t v)
{
    lv_img_set_angle((lv_obj_t*)img, v);
}

void clock_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*CLOCK_H*/
