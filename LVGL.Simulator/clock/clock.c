#include "clock.h"

void initClockBg()
{
    //去掉滚动条
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(lv_scr_act(), LV_SCROLLBAR_MODE_OFF);

    //背景
    lv_obj_t* bgimg = lv_img_create(lv_scr_act());

    lv_img_set_src(bgimg, &star_bg); // S3直接用196x196的背景图

    lv_obj_align(bgimg, LV_ALIGN_CENTER, 0, 0);

    //右上齿轮
    lv_obj_t* right_top_gear = lv_img_create(lv_scr_act());
    lv_img_set_src(right_top_gear, &Horoscope03);

#if LIYUE_VER
    lv_obj_align(right_top_gear, LV_ALIGN_CENTER, 27, 3);
#else
    lv_obj_align(right_top_gear, LV_ALIGN_CENTER, 22, -17);
#endif

    //左下大齿轮
    lv_obj_t* left_btm_gear = lv_img_create(lv_scr_act());
    lv_img_set_src(left_btm_gear, &Horoscope04);
#if LIYUE_VER
    lv_obj_align(left_btm_gear, LV_ALIGN_CENTER, -37, -9);
#else
    lv_obj_align(left_btm_gear, LV_ALIGN_CENTER, -33, 20);
#endif

    //中心齿轮
    lv_obj_t* center_gear = lv_img_create(lv_scr_act());
    lv_img_set_src(center_gear, &Horoscope06);
    lv_obj_align(center_gear, LV_ALIGN_CENTER, 0, 0);

    //右下中齿轮
    lv_obj_t* right_btm_gear = lv_img_create(lv_scr_act());
    lv_img_set_src(right_btm_gear, &Horoscope05);
#if LIYUE_VER
    lv_obj_align(right_btm_gear, LV_ALIGN_CENTER, 28, 110);
#else
    lv_obj_align(right_btm_gear, LV_ALIGN_CENTER, 97, 59);
#endif

    //顶层遮罩
    lv_obj_t* mask_img = lv_img_create(lv_scr_act());
#if LIYUE_VER
    lv_img_set_src(mask_img, &star_mask_liyue);
#else
    lv_img_set_src(mask_img, &star_mask);
#endif
    lv_obj_align(mask_img, LV_ALIGN_CENTER, 0, 0);

    //齿轮动画效果
    lv_anim_init(&anim_center_gear);
    lv_anim_set_var(&anim_center_gear, center_gear);
    lv_anim_set_exec_cb(&anim_center_gear, rotate_img);
    lv_anim_set_values(&anim_center_gear, 3600, 0);
    lv_anim_set_time(&anim_center_gear, 75000);
    lv_anim_set_repeat_count(&anim_center_gear, LV_ANIM_REPEAT_INFINITE);

    lv_anim_init(&anim_left_btm_gear);
    lv_anim_set_var(&anim_left_btm_gear, left_btm_gear);
    lv_anim_set_exec_cb(&anim_left_btm_gear, rotate_img);
    lv_anim_set_values(&anim_left_btm_gear, 3600, 0);
    lv_anim_set_time(&anim_left_btm_gear, 75000);
    lv_anim_set_repeat_count(&anim_left_btm_gear, LV_ANIM_REPEAT_INFINITE);

    lv_anim_init(&anim_right_top_gear);
    lv_anim_set_var(&anim_right_top_gear, right_top_gear);
    lv_anim_set_exec_cb(&anim_right_top_gear, rotate_img);
    lv_anim_set_values(&anim_right_top_gear, 3600, 0);
    lv_anim_set_time(&anim_right_top_gear, 75000);
    lv_anim_set_repeat_count(&anim_right_top_gear, LV_ANIM_REPEAT_INFINITE);

    lv_anim_init(&anim_right_btm_gear);
    lv_anim_set_var(&anim_right_btm_gear, right_btm_gear);
    lv_anim_set_exec_cb(&anim_right_btm_gear, rotate_img);
    lv_anim_set_values(&anim_right_btm_gear, 0, 3600);
    lv_anim_set_time(&anim_right_btm_gear, 50000); //根据齿比计算得，为了让齿轮咬合完全一致
    lv_anim_set_repeat_count(&anim_right_btm_gear, LV_ANIM_REPEAT_INFINITE);

    lv_anim_start(&anim_center_gear);
    lv_anim_start(&anim_left_btm_gear);
    lv_anim_start(&anim_right_top_gear);
    lv_anim_start(&anim_right_btm_gear);

}

bool _isClockInit = false;

uint32_t last_timestamp = 0;

uint8_t clockMode = 0; //0普通时分秒 1隐藏秒的圆弧形

uint16_t hPos = 0; //快进或者后退模式，时针的当前位置，角度x10，0-3600

uint16_t mPos = 0; //分针的当前位置，角度x10，0-3600

uint32_t nextTick = 0; //用于快进和后退的时间戳
#if LIYUE_VER
uint8_t last_m = 60; //最后的分钟
#endif
uint8_t opa[4] = { 0, 0, 0, 0 }; //月 ，日出 日中 日落

// uint32_t last_timestamp = 0;
// static uint32_t currtimestamp = 1664781120;
SYSTEMTIME last_time, current_time;

void refresh()
{
    uint8_t hr = current_time.wHour;
    if (hr == 0)
        hr = 12;
    else if (hr > 12)
        hr -= 12;
#if LIYUE_VER
    hPos = hr * 300 + current_time.wMinute * 5 + 450;
#else
    hPos = hr * 300 + current_time.wMinute * 5;
#endif
    lv_img_set_angle(lvHour, hPos);
#if LIYUE_VER
    mPos = current_time.wMinute * 60 + 450;
#else
    mPos = current_time.wMinute * 60;
#endif
    lv_img_set_angle(lvMinute, mPos);
#if LIYUE_VER
    lv_img_set_angle(lvSecond, current_time.wSecond * 60 + 450);
#else
    lv_img_set_angle(lvSecond, current_time.wSecond * 60);
#endif

#if LIYUE_VER
    if (clock_time.minute() != last_m)
    {
        last_m = clock_time.minute();
        calcOpa();
        lv_obj_set_style_img_opa(lvMoonrise, opa[0], 0);
        lv_obj_set_style_img_opa(lvSunrise, opa[1], 0);
        lv_obj_set_style_img_opa(lvDaytime, opa[2], 0);
        lv_obj_set_style_img_opa(lvSunset, opa[3], 0);
    }

#endif
}

bool isTimeChanged()
{
    // SYSTEMTIME st, lt;
    GetLocalTime(&current_time);
    if ((current_time.wHour != last_time.wHour) || (current_time.wMinute != last_time.wMinute) || (current_time.wSecond != last_time.wSecond))
    {
        printf("Changed\n");
        last_time.wHour = current_time.wHour;
        last_time.wMinute = current_time.wMinute;
        last_time.wSecond = current_time.wSecond;
        return true;
    }
    else {
        printf("Not changed\n");
        return false;
    }
}

static void clock_timer_task(lv_timer_t* t)
{
    if (isTimeChanged())
    {
        refresh();
    }
}

void clock_init(void)
{
    last_time.wHour = 10;
    last_time.wMinute = 13;
    last_time.wSecond = 25;
    
    initClockBg();

    uint8_t hr = 8;
#if LIYUE_VER
    last_m = clock_time.minute();
#endif
    lvHour = lv_img_create(lv_scr_act());
    lv_img_set_src(lvHour, &hand_h);
    lv_obj_align(lvHour, LV_ALIGN_CENTER, 0, -44);
    lv_img_set_pivot(lvHour, 16, 81);
#if LIYUE_VER
    hPos = hr * 300 + clock_time.minute() * 5 + 450;
#else
    // hPos = hr * 300 + clock_time.minute() * 5;
    hPos = hr * 300 + 15 * 5;
#endif
    lv_img_set_angle(lvHour, hPos);

    lvMinute = lv_img_create(lv_scr_act());
    lv_img_set_src(lvMinute, &hand_m);
    lv_obj_align(lvMinute, LV_ALIGN_CENTER, 0, -43);
    lv_img_set_pivot(lvMinute, 12, 92);
#if LIYUE_VER
    mPos = clock_time.minute() * 60 + 450;
#else
    // mPos = clock_time.minute() * 60;
    mPos = 15 * 60;
#endif
    lv_img_set_angle(lvMinute, mPos);

    lvSecond = lv_img_create(lv_scr_act());
    lv_img_set_src(lvSecond, &hand_s);
    lv_obj_align(lvSecond, LV_ALIGN_CENTER, 0, -58);
    lv_img_set_pivot(lvSecond, 6, 110);
#if LIYUE_VER
    lv_img_set_angle(lvSecond, clock_time.second() * 60 + 450);
#else
    // lv_img_set_angle(lvSecond, clock_time.second() * 60);
    lv_img_set_angle(lvSecond, 44 * 60);
#endif

    //初始化圆弧
    arc = lv_arc_create(lv_scr_act());
    lv_arc_set_mode(arc, LV_ARC_MODE_NORMAL);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);

    lv_arc_set_bg_start_angle(arc, mPos < 900 ? 270 + mPos / 10 : (mPos - 900) / 10);
    lv_arc_set_bg_end_angle(arc, hPos < 900 ? 270 + hPos / 10 : (hPos - 900) / 10);

    lv_obj_set_size(arc, 192, 192);
    lv_obj_align(arc, LV_ALIGN_CENTER, 0, 0);
    lv_style_init(&arc_style);
    lv_style_set_arc_img_src(&arc_style, &arc_mask);
    lv_style_set_arc_width(&arc_style, 4);
    lv_style_set_arc_rounded(&arc_style, false);
    lv_obj_add_style(arc, &arc_style, 0);
    lv_obj_center(arc);

    lv_obj_add_flag(arc, LV_OBJ_FLAG_HIDDEN);
    /*
    lv_anim_init(&anim_hand_s);
    lv_anim_set_var(&anim_hand_s, lvSecond);
    lv_anim_set_exec_cb(&anim_hand_s, rotate_img);
    lv_anim_set_values(&anim_hand_s, 0, 3600);
    lv_anim_set_time(&anim_hand_s, 60000); //根据齿比计算得，为了让齿轮咬合完全一致
    lv_anim_set_repeat_count(&anim_hand_s, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&anim_hand_s);
    */
    clock_timer = lv_timer_create(clock_timer_task, 20, NULL);
    lv_timer_pause(clock_timer);
    // lv_timer_resume(clock_timer);
    
    //初始化图标，仅限方屏
#if LIYUE_VER
    calcOpa();

    lvMoonrise = lv_img_create(lv_scr_act());
    lv_img_set_src(lvMoonrise, &moonrise);
    lv_obj_align(lvMoonrise, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_style_img_opa(lvMoonrise, opa[0], 0); //透明度范围是0-255  每分钟更新一次

    lvSunrise = lv_img_create(lv_scr_act());
    lv_img_set_src(lvSunrise, &sunrise);
    lv_obj_align(lvSunrise, LV_ALIGN_TOP_LEFT, opa[0], 0);
    lv_obj_set_style_img_opa(lvSunrise, opa[1], 0);

    lvDaytime = lv_img_create(lv_scr_act());
    lv_img_set_src(lvDaytime, &daytime);
    lv_obj_align(lvDaytime, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_img_opa(lvDaytime, opa[2], 0);

    lvSunset = lv_img_create(lv_scr_act());
    lv_img_set_src(lvSunset, &sunset);
    lv_obj_align(lvSunset, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_style_img_opa(lvSunset, opa[3], 0);
#endif
}
