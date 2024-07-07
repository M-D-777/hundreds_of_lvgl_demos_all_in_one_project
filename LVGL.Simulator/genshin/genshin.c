#include <stdio.h>
#include "../lvgl/lvgl.h"

lv_obj_t* img_background;
lv_obj_t* img_background2;
lv_obj_t* container;

lv_obj_t* bar;

lv_obj_t* img;
const uint8_t start_color = 210;
static uint8_t fade_color = 0;
const int16_t end_size_x = 420;
static int16_t fade_size_x = 0;
static int8_t diff = -4;
lv_timer_t* mihoyo_timer;
lv_timer_t* genshin_timer;
lv_timer_t* jindu_timer;

void mihoyo_timer_task(lv_timer_t* timer)
{
    //printf("mihoyo_timer_task\r\n");
    //static inline lv_color_t lv_color_make(uint8_t r, uint8_t g, uint8_t b)
    // lv_color_hex(user_data)

    //lv_color_hex
    //lv_obj_set_style_bg_color(img_background, lv_color_make(start_color, start_color, start_color), 0);
    
    if (fade_color <= 20)
    {
        diff = 4;
    }
    if (fade_color >= start_color - diff)
    {
        fade_color = start_color;
        diff = -4;
        lv_obj_set_size(img_background, 320, 246);
        lv_img_set_src(img, "A:genshin_320.png");
        lv_obj_add_flag(img_background, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
        lv_timer_pause(mihoyo_timer);
        lv_timer_resume(genshin_timer);
        //printf("test\r\n");
        return;
    }
    lv_obj_set_style_bg_color(img_background, lv_color_make(fade_color, fade_color, fade_color), 0);
    fade_color += diff;

}

static uint8_t delay_counter = 0;

void genshin_timer_task2(lv_timer_t* timer)
{
    if (delay_counter < 100)
    {
        delay_counter += 5;
        //printf("delay\r\n");
    }
    else
    {
        //delay_counter = 0;
        lv_obj_clear_flag(img_background, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
        if (fade_color <= 30)
        {
            diff = 4;
        }
        if (fade_color >= start_color - diff)
        {
            fade_color = start_color;
            diff = -4;
            lv_obj_set_size(img_background, 0, 192);
            lv_obj_set_align(img_background, LV_ALIGN_LEFT_MID);
            //lv_obj_align_to(img_background, img, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
            lv_obj_set_x(img_background, 190);
            //lv_obj_set_y(img_background, 40);
            lv_img_set_src(img, "A:result_400.png");
            //lv_obj_add_flag(img_background, LV_OBJ_FLAG_HIDDEN);
            //lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
            //img_background2 = lv_obj_create(lv_scr_act());
            lv_obj_set_size(img_background2, 420, 192);
            lv_obj_set_align(img_background2, LV_ALIGN_LEFT_MID);
            lv_obj_set_x(img_background2, 190);
            //lv_obj_remove_style_all(img_background);
            fade_color = start_color;
            lv_obj_set_style_bg_color(img_background2, lv_color_make(fade_color-50, fade_color-50, fade_color-50), 0);
            lv_timer_pause(genshin_timer);
            lv_timer_resume(jindu_timer);
            delay_counter = 0;
            return;
        }
        lv_obj_set_style_bg_color(img_background, lv_color_make(fade_color, fade_color, fade_color), 0);
        fade_color += diff;
    }
}

void genshin_timer_task(lv_timer_t* timer)
{
    if (delay_counter < 100)
    {
        delay_counter += 5;
        //printf("delay\r\n");
    }
    else
    {
        //delay_counter = 0;
        lv_obj_clear_flag(img_background, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
        if (fade_color <= 20)
        {
            diff = 4;
        }
        if (fade_color >= start_color - diff)
        {
            fade_color = start_color;
            diff = -4;
            lv_obj_set_size(img_background, 0, 192);
            lv_obj_set_align(img_background, LV_ALIGN_LEFT_MID);
            //lv_obj_align_to(img_background, img, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
            lv_obj_set_x(img_background, 190);
            //lv_obj_set_y(img_background, 40);
            lv_img_set_src(img, "A:result_400.png");
            //lv_obj_add_flag(img_background, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
            //img_background2 = lv_obj_create(lv_scr_act());
            lv_obj_set_size(img_background2, 420, 192);
            lv_obj_set_align(img_background2, LV_ALIGN_LEFT_MID);
            lv_obj_set_x(img_background2, 190);
            //lv_obj_remove_style_all(img_background);
            fade_color = start_color;
            lv_obj_set_style_bg_color(img_background2, lv_color_make(fade_color - 50, fade_color - 50, fade_color - 50), 0);
            lv_timer_pause(genshin_timer);
            lv_timer_resume(jindu_timer);
            delay_counter = 0;
            return;
        }
        lv_obj_set_style_bg_color(img_background, lv_color_make(fade_color, fade_color, fade_color), 0);
        fade_color += diff;
    }
}
int val = 0;
int counter = 0;
void jindu_timer_task(lv_timer_t* timer)
{
    if (delay_counter < 100)
    {
        delay_counter += 5;
        //printf("delay\r\n");
    }
    else
    {
        if (val == 0)
        {
            lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(bar, LV_OBJ_FLAG_HIDDEN);
        }
        lv_bar_set_value(bar, val, LV_ANIM_ON);
        if (val != 90)
        {
            val += 1;
        }
        else {
            if(counter < 35)
            {
                counter += 1;
            }
            else {
                val = 91;
            }
        }
        //printf("val:%d\r\n", val);
        if (val > 100)
        {
            lv_timer_pause(jindu_timer);
            return;
        }

    }
}

void jindu_timer_task2(lv_timer_t* timer)
{
    if (delay_counter < 100)
    {
        delay_counter += 5;
        printf("delay\r\n");
    }
    else
    {
        //delay_counter = 0;
        lv_obj_clear_flag(img_background, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(img_background2, LV_OBJ_FLAG_HIDDEN);
        //lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
        //fade_size_x
        lv_obj_set_size(img_background, fade_size_x, 192);
        lv_obj_set_x(img_background2, 190 + fade_size_x);
        lv_obj_set_size(img_background2, 420 - fade_size_x, 192);
        fade_size_x += 2;
        if (fade_size_x > end_size_x)
        {
            printf("fade_size_x:%d, end_size_x:%d\r\n", fade_size_x, end_size_x);
            lv_timer_pause(jindu_timer);
            return;
        }
        
    }
}

void genshin_start(void)
{
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    img_background = lv_obj_create(lv_scr_act());
    //lv_obj_remove_style_all(img_background);
    fade_color = start_color;
    lv_obj_set_style_bg_color(img_background, lv_color_make(fade_color, fade_color, fade_color), 0);
    //lv_obj_set_style_border_color(img_background, lv_color_hex(rnd_next(0, 0xFFFFF0)), 0);
    //lv_obj_set_style_shadow_color(img_background, lv_color_hex(rnd_next(0, 0xFFFFF0)), 0);

    lv_obj_set_size(img_background, 320, 131);
    lv_obj_align(img_background, LV_ALIGN_CENTER, 0, 0);

    img_background2 = lv_obj_create(lv_scr_act());
    lv_obj_add_flag(img_background2, LV_OBJ_FLAG_HIDDEN);

    bar = lv_bar_create(lv_scr_act());
    lv_obj_align(bar, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(bar, 400, 57);
    lv_obj_add_flag(bar, LV_OBJ_FLAG_HIDDEN);
    lv_bar_set_value(bar, 0, LV_ANIM_ON);

    //Write style for screen_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(bar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(bar, lv_color_hex(0xDFDFDF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(bar, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style for screen_bar_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(bar, 125, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(bar, lv_color_hex(0x202020), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(bar, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_anim_time(bar, 0, 0);
    lv_bar_set_value(bar, 0, LV_ANIM_ON);

    //container = lv_obj_create(lv_scr_act());
    //lv_obj_set_size(container, 160, 57);
    //img = lv_img_create(container);
    //lv_obj_align(img, LV_ALIGN_TOP_LEFT, 0, 0);
    img = lv_img_create(lv_scr_act());
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(img, "A:mihoyo_320.png");
    //lv_img_set_src(img, "A:wink.png");

    mihoyo_timer = lv_timer_create(mihoyo_timer_task, 60, img_background);
    lv_timer_pause(mihoyo_timer);
    lv_timer_resume(mihoyo_timer);

    genshin_timer = lv_timer_create(genshin_timer_task, 60, img_background);
    lv_timer_pause(genshin_timer);
    //lv_timer_resume(genshin_timer);

    jindu_timer = lv_timer_create(jindu_timer_task, 60, img_background);
    lv_timer_pause(jindu_timer);
    //lv_timer_resume(genshin_timer);
}
