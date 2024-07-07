#include <stdio.h>
#include "../lvgl/lvgl.h"

lv_obj_t* img_background;
lv_obj_t* img;
static uint8_t start_color = 148;
static uint8_t fade_color = 0;
static int8_t diff = -4;
lv_timer_t* mihoyo_timer;
lv_timer_t* genshin_timer;

void mihoyo_timer_task(lv_timer_t* timer)
{
    printf("mihoyo_timer_task\r\n");
    //static inline lv_color_t lv_color_make(uint8_t r, uint8_t g, uint8_t b)
    // lv_color_hex(user_data)

    //lv_color_hex
    lv_obj_set_style_bg_color(img_background, lv_color_make(start_color, start_color, start_color), 0);
    start_color += diff;
    if (start_color <= 30)
    {
        diff = 4;
    }
    if (start_color >= fade_color - diff)
    {
        start_color = fade_color;
        diff = -4;
        //lv_obj_set_size(img_background, 320, 246);
        //lv_img_set_src(img, "A:genshin_320.png");
        //lv_obj_add_flag(img_background, LV_OBJ_FLAG_HIDDEN);
        //lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
        lv_timer_pause(mihoyo_timer);
        //lv_timer_resume(genshin_timer);
        printf("test\r\n");
    }
    lv_obj_set_style_bg_color(img_background, lv_color_make(start_color, start_color, start_color), 0);

}

void mihoyo_timer_task2(lv_timer_t* timer)
{
    printf("mihoyo_timer_task\r\n");
    //static inline lv_color_t lv_color_make(uint8_t r, uint8_t g, uint8_t b)
    // lv_color_hex(user_data)

    //lv_color_hex
    //lv_obj_set_style_bg_color(img_background, lv_color_make(start_color, start_color, start_color), 0);
    start_color += diff;
    if (start_color <= 30)
    {
        diff = 4;
    }
    if (start_color >= 200)
    {
        start_color = 200;
        diff = -4;
        //lv_obj_set_size(img_background, 320, 246);
        //lv_img_set_src(img, "A:genshin_320.png");
        //lv_obj_add_flag(img_background, LV_OBJ_FLAG_HIDDEN);
        //lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
        lv_timer_pause(mihoyo_timer);
        //lv_timer_resume(genshin_timer);
        printf("test3\r\n");
    }
    //lv_obj_set_style_opa(img, LV_OPA_TRANSP, start_color);
    //lv_obj_set_style_img_recolor_opa(img, start_color, 0);
    lv_obj_set_style_img_recolor(img, lv_color_make(start_color, start_color, start_color), 0);
    //lv_obj_set_style_bg_color(img_background, lv_color_make(start_color, start_color, start_color), 0);

}

static uint8_t delay_counter = 0;

void genshin_timer_task(lv_timer_t* timer)
{
    //static inline lv_color_t lv_color_make(uint8_t r, uint8_t g, uint8_t b)
    // lv_color_hex(user_data)

    //lv_color_hex
    if (delay_counter < 100)
    {
        delay_counter += 5;
        printf("delay\r\n");
    }
    else
    {
        lv_obj_clear_flag(img_background, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
        start_color += diff;
        if (start_color <= 30)
        {
            diff = 4;
        }
        if (start_color >= 150)
        {

            start_color = 150;
            diff = -4;
            //lv_obj_set_size(img_background, 320, 246);
            //lv_img_set_src(img, "A:genshin_320.png");
            //lv_obj_add_flag(img_background, LV_OBJ_FLAG_HIDDEN);
            //lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
            //lv_timer_resume(genshin_timer);
            printf("test2\r\n");
            lv_timer_pause(genshin_timer);
        }
        lv_obj_set_style_bg_color(img_background, lv_color_make(start_color, start_color, start_color), 0);
    }
}

void genshin_start(void)
{
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    img_background = lv_obj_create(lv_scr_act());
    //lv_obj_remove_style_all(img_background);
    lv_obj_set_style_bg_color(img_background, lv_color_make(start_color, start_color, start_color), 0);
    //lv_obj_set_style_border_color(img_background, lv_color_hex(rnd_next(0, 0xFFFFF0)), 0);
    //lv_obj_set_style_shadow_color(img_background, lv_color_hex(rnd_next(0, 0xFFFFF0)), 0);

    lv_obj_set_size(img_background, 320, 131);
    lv_obj_align(img_background, LV_ALIGN_CENTER, 0, 0);


    img = lv_img_create(lv_scr_act());
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(img, "A:mihoyo_320.png");

    mihoyo_timer = lv_timer_create(mihoyo_timer_task, 50, img_background);
    lv_timer_pause(mihoyo_timer);
    lv_timer_resume(mihoyo_timer);

    genshin_timer = lv_timer_create(genshin_timer_task, 20, img_background);
    lv_timer_pause(genshin_timer);
    //lv_timer_resume(genshin_timer);
}

void genshin_start3(void)
{
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    img_background = lv_obj_create(lv_scr_act());
    //lv_obj_remove_style_all(img_background);
    lv_obj_set_style_bg_color(img_background, lv_color_make(start_color, start_color, start_color), 0);
    //lv_obj_set_style_border_color(img_background, lv_color_hex(rnd_next(0, 0xFFFFF0)), 0);
    //lv_obj_set_style_shadow_color(img_background, lv_color_hex(rnd_next(0, 0xFFFFF0)), 0);

    lv_obj_set_size(img_background, 320, 120);
    lv_obj_align(img_background, LV_ALIGN_CENTER, 0, 0);


    img = lv_img_create(lv_scr_act());
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    LV_IMG_DECLARE(mihayou_convert);
    lv_img_set_src(img, &mihayou_convert);
    //lv_img_set_src(img, "A:wink.png");

    //lv_obj_set_style_opa(img, LV_OPA_TRANSP, 100);
    lv_obj_set_style_img_recolor_opa(img, 127, 0);
    lv_obj_set_style_img_recolor(img, lv_color_make(start_color, start_color, start_color), 0);

    mihoyo_timer = lv_timer_create(mihoyo_timer_task, 50, img_background);
    lv_timer_pause(mihoyo_timer);
    lv_timer_resume(mihoyo_timer);

    lv_obj_add_flag(img_background, LV_OBJ_FLAG_HIDDEN);
}
