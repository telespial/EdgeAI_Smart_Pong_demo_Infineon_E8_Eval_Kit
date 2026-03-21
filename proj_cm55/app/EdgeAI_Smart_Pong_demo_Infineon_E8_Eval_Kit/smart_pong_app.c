#include "smart_pong_app.h"

static void make_title(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "SMART PONG - PORT PREP");
    lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 24);
}

static void make_status(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label,
        "Display + touch + LVGL are up.\\n"
        "Next: add paddles, ball physics, and input mapping.");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void smart_pong_app_start(void)
{
    lv_obj_t *screen = lv_screen_active();

    lv_obj_set_style_bg_color(screen, lv_palette_main(LV_PALETTE_BLUE_GREY), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(screen, lv_palette_lighten(LV_PALETTE_BLUE, 3), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(screen, LV_GRAD_DIR_VER, LV_PART_MAIN);

    make_title(screen);
    make_status(screen);
}
