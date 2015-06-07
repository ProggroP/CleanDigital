#pragma once

enum KEYS
{
	KEY_INVERT = 0x0
};

struct tm *s_tick_time;
Window *s_main_window;
GFont s_font_clock, s_font_date;
TextLayer *s_clock_layer, *s_date_layer;
Layer *s_battery_layer;
InverterLayer *s_inverter_layer;
int s_battery_pct = 0;
