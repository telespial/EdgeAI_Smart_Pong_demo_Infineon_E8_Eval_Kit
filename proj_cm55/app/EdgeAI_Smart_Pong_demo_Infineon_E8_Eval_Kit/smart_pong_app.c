#include "smart_pong_app.h"

#define PADDLE_W            (12)
#define PADDLE_H            (96)
#define BALL_SIZE           (14)
#define GAME_TICK_MS        (16)
#define BALL_SPEED_X        (6)
#define BALL_SPEED_Y        (4)
#define AI_TRACK_SPEED      (5)
#define EDGE_MARGIN         (16)
#define SCORE_TO_WIN        (7)

typedef struct
{
    lv_obj_t *screen;
    lv_obj_t *paddle_left;
    lv_obj_t *paddle_right;
    lv_obj_t *ball;
    lv_obj_t *score_left_lbl;
    lv_obj_t *score_right_lbl;
    lv_obj_t *status_lbl;
    lv_timer_t *timer;
    int32_t ball_x;
    int32_t ball_y;
    int32_t ball_vx;
    int32_t ball_vy;
    uint16_t score_left;
    uint16_t score_right;
    int16_t screen_w;
    int16_t screen_h;
} smart_pong_ctx_t;

static smart_pong_ctx_t g_ctx;

static int32_t clamp_i32(int32_t value, int32_t min_value, int32_t max_value)
{
    if (value < min_value)
    {
        return min_value;
    }
    if (value > max_value)
    {
        return max_value;
    }
    return value;
}

static void set_paddle_center_y(lv_obj_t *paddle, int32_t center_y, int32_t screen_h)
{
    int32_t min_center = (PADDLE_H / 2) + EDGE_MARGIN;
    int32_t max_center = screen_h - (PADDLE_H / 2) - EDGE_MARGIN;
    int32_t clamped = clamp_i32(center_y, min_center, max_center);
    lv_obj_set_y(paddle, clamped - (PADDLE_H / 2));
}

static void refresh_score_labels(void)
{
    lv_label_set_text_fmt(g_ctx.score_left_lbl, "%u", (unsigned int)g_ctx.score_left);
    lv_label_set_text_fmt(g_ctx.score_right_lbl, "%u", (unsigned int)g_ctx.score_right);
}

static void reset_ball(int32_t direction)
{
    g_ctx.ball_x = (g_ctx.screen_w / 2) - (BALL_SIZE / 2);
    g_ctx.ball_y = (g_ctx.screen_h / 2) - (BALL_SIZE / 2);
    g_ctx.ball_vx = (direction >= 0) ? BALL_SPEED_X : -BALL_SPEED_X;
    g_ctx.ball_vy = BALL_SPEED_Y;
}

static void set_status_text(void)
{
    if (g_ctx.score_left >= SCORE_TO_WIN)
    {
        lv_label_set_text(g_ctx.status_lbl, "PLAYER WINS - TAP/DRAG LEFT SIDE");
    }
    else if (g_ctx.score_right >= SCORE_TO_WIN)
    {
        lv_label_set_text(g_ctx.status_lbl, "CPU WINS - TAP/DRAG LEFT SIDE");
    }
    else
    {
        lv_label_set_text(g_ctx.status_lbl, "SMART PONG PRE-ALPHA");
    }
}

static void score_point(int32_t scored_by_left)
{
    if (scored_by_left != 0)
    {
        g_ctx.score_left++;
        reset_ball(-1);
    }
    else
    {
        g_ctx.score_right++;
        reset_ball(1);
    }

    if ((g_ctx.score_left >= SCORE_TO_WIN) || (g_ctx.score_right >= SCORE_TO_WIN))
    {
        g_ctx.score_left = 0;
        g_ctx.score_right = 0;
    }

    refresh_score_labels();
    set_status_text();
}

static void on_touch_update(lv_event_t *event)
{
    LV_UNUSED(event);
    lv_indev_t *indev = lv_indev_active();
    lv_point_t p;

    if (indev == NULL)
    {
        return;
    }

    lv_indev_get_point(indev, &p);
    if (p.x <= (g_ctx.screen_w / 2))
    {
        set_paddle_center_y(g_ctx.paddle_left, p.y, g_ctx.screen_h);
    }
}

static void game_tick_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    int32_t left_x = lv_obj_get_x(g_ctx.paddle_left);
    int32_t left_y = lv_obj_get_y(g_ctx.paddle_left);
    int32_t right_x = lv_obj_get_x(g_ctx.paddle_right);
    int32_t right_y = lv_obj_get_y(g_ctx.paddle_right);
    int32_t next_ball_x = g_ctx.ball_x + g_ctx.ball_vx;
    int32_t next_ball_y = g_ctx.ball_y + g_ctx.ball_vy;
    int32_t ball_center_y = next_ball_y + (BALL_SIZE / 2);
    int32_t right_center_y = right_y + (PADDLE_H / 2);

    /* Simple AI that follows ball center with capped speed */
    if (right_center_y < ball_center_y)
    {
        set_paddle_center_y(g_ctx.paddle_right, right_center_y + AI_TRACK_SPEED, g_ctx.screen_h);
    }
    else if (right_center_y > ball_center_y)
    {
        set_paddle_center_y(g_ctx.paddle_right, right_center_y - AI_TRACK_SPEED, g_ctx.screen_h);
    }

    if (next_ball_y <= EDGE_MARGIN)
    {
        next_ball_y = EDGE_MARGIN;
        g_ctx.ball_vy = -g_ctx.ball_vy;
    }
    else if (next_ball_y + BALL_SIZE >= g_ctx.screen_h - EDGE_MARGIN)
    {
        next_ball_y = g_ctx.screen_h - EDGE_MARGIN - BALL_SIZE;
        g_ctx.ball_vy = -g_ctx.ball_vy;
    }

    if ((next_ball_x <= (left_x + PADDLE_W)) &&
        (next_ball_x + BALL_SIZE >= left_x) &&
        (next_ball_y + BALL_SIZE >= left_y) &&
        (next_ball_y <= left_y + PADDLE_H) &&
        (g_ctx.ball_vx < 0))
    {
        next_ball_x = left_x + PADDLE_W;
        g_ctx.ball_vx = -g_ctx.ball_vx;
    }

    if ((next_ball_x + BALL_SIZE >= right_x) &&
        (next_ball_x <= right_x + PADDLE_W) &&
        (next_ball_y + BALL_SIZE >= right_y) &&
        (next_ball_y <= right_y + PADDLE_H) &&
        (g_ctx.ball_vx > 0))
    {
        next_ball_x = right_x - BALL_SIZE;
        g_ctx.ball_vx = -g_ctx.ball_vx;
    }

    if (next_ball_x < 0)
    {
        score_point(0);
        return;
    }
    if (next_ball_x + BALL_SIZE > g_ctx.screen_w)
    {
        score_point(1);
        return;
    }

    g_ctx.ball_x = next_ball_x;
    g_ctx.ball_y = next_ball_y;
    lv_obj_set_pos(g_ctx.ball, g_ctx.ball_x, g_ctx.ball_y);
}

void smart_pong_app_start(void)
{
    g_ctx.screen = lv_screen_active();
    g_ctx.screen_w = lv_display_get_horizontal_resolution(NULL);
    g_ctx.screen_h = lv_display_get_vertical_resolution(NULL);
    g_ctx.score_left = 0;
    g_ctx.score_right = 0;

    lv_obj_set_style_bg_color(g_ctx.screen, lv_color_hex(0x0f172a), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(g_ctx.screen, lv_color_hex(0x111827), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(g_ctx.screen, LV_GRAD_DIR_VER, LV_PART_MAIN);

    g_ctx.score_left_lbl = lv_label_create(g_ctx.screen);
    lv_obj_set_style_text_font(g_ctx.score_left_lbl, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(g_ctx.score_left_lbl, LV_ALIGN_TOP_MID, -60, 10);

    g_ctx.score_right_lbl = lv_label_create(g_ctx.screen);
    lv_obj_set_style_text_font(g_ctx.score_right_lbl, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_align(g_ctx.score_right_lbl, LV_ALIGN_TOP_MID, 60, 10);

    g_ctx.status_lbl = lv_label_create(g_ctx.screen);
    lv_obj_set_style_text_color(g_ctx.status_lbl, lv_color_hex(0x93c5fd), LV_PART_MAIN);
    lv_obj_align(g_ctx.status_lbl, LV_ALIGN_TOP_MID, 0, 52);

    lv_obj_t *center_line = lv_line_create(g_ctx.screen);
    static lv_point_precise_t points[] = {{0, 0}, {0, 460}};
    lv_line_set_points(center_line, points, 2);
    lv_obj_set_style_line_width(center_line, 2, LV_PART_MAIN);
    lv_obj_set_style_line_color(center_line, lv_color_hex(0x334155), LV_PART_MAIN);
    lv_obj_set_pos(center_line, g_ctx.screen_w / 2, EDGE_MARGIN);

    g_ctx.paddle_left = lv_obj_create(g_ctx.screen);
    lv_obj_set_size(g_ctx.paddle_left, PADDLE_W, PADDLE_H);
    lv_obj_set_style_bg_color(g_ctx.paddle_left, lv_color_hex(0x22d3ee), LV_PART_MAIN);
    lv_obj_set_style_radius(g_ctx.paddle_left, 6, LV_PART_MAIN);
    lv_obj_set_style_border_width(g_ctx.paddle_left, 0, LV_PART_MAIN);
    lv_obj_set_pos(g_ctx.paddle_left, EDGE_MARGIN, (g_ctx.screen_h / 2) - (PADDLE_H / 2));

    g_ctx.paddle_right = lv_obj_create(g_ctx.screen);
    lv_obj_set_size(g_ctx.paddle_right, PADDLE_W, PADDLE_H);
    lv_obj_set_style_bg_color(g_ctx.paddle_right, lv_color_hex(0xf43f5e), LV_PART_MAIN);
    lv_obj_set_style_radius(g_ctx.paddle_right, 6, LV_PART_MAIN);
    lv_obj_set_style_border_width(g_ctx.paddle_right, 0, LV_PART_MAIN);
    lv_obj_set_pos(g_ctx.paddle_right, g_ctx.screen_w - EDGE_MARGIN - PADDLE_W, (g_ctx.screen_h / 2) - (PADDLE_H / 2));

    g_ctx.ball = lv_obj_create(g_ctx.screen);
    lv_obj_set_size(g_ctx.ball, BALL_SIZE, BALL_SIZE);
    lv_obj_set_style_bg_color(g_ctx.ball, lv_color_hex(0xf8fafc), LV_PART_MAIN);
    lv_obj_set_style_radius(g_ctx.ball, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_border_width(g_ctx.ball, 0, LV_PART_MAIN);

    refresh_score_labels();
    set_status_text();
    reset_ball(1);
    lv_obj_set_pos(g_ctx.ball, g_ctx.ball_x, g_ctx.ball_y);

    lv_obj_add_event_cb(g_ctx.screen, on_touch_update, LV_EVENT_PRESSING, NULL);
    lv_obj_add_event_cb(g_ctx.screen, on_touch_update, LV_EVENT_CLICKED, NULL);

    g_ctx.timer = lv_timer_create(game_tick_cb, GAME_TICK_MS, NULL);
}
