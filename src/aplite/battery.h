#include <pebble.h>

/*
 *	battery.h
 *		Contains update procedures for battery and plugged-icon layers
 */

#define BATTERY_METER_MAX_WIDTH  124
#define BATTERY_TOP_LINE_X        97
#define BATTERY_METER_LINE_X      98

static int CALC_BATTERY_METER_WIDTH(int battery)
{
	double pct = battery / 100.0;
	return (int)(BATTERY_METER_MAX_WIDTH * pct);
}

static void update_battery_proc(Layer *this_layer, GContext *ctx)
{
	graphics_context_set_stroke_color(ctx, GColorWhite);

	GPoint top_left  = GPoint(10, BATTERY_TOP_LINE_X);
	GPoint top_right = GPoint(10 + BATTERY_METER_MAX_WIDTH,
							  BATTERY_TOP_LINE_X);
	graphics_draw_line(ctx, top_left, top_right);

	GPoint meter_left  = GPoint(10, BATTERY_METER_LINE_X);
	GPoint meter_right = GPoint(10 + CALC_BATTERY_METER_WIDTH(s_battery_pct),
								BATTERY_METER_LINE_X);
	graphics_draw_line(ctx, meter_left, meter_right);
}
