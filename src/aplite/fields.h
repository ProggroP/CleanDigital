#pragma once

#define CLOCK_FONT_ID  RESOURCE_ID_FONT_CLOCK_54
#define DATE_FONT_ID   RESOURCE_ID_FONT_MONTH_28

#define DEFVAL_DATE    "30 Jan"
#define DEFVAL_TIME    "00:00"

enum KEYS
{
	KEY_INVERT = 0x0
};

// global fields
struct tm *s_tick_time;
int  s_battery_pct = 0;
bool s_plugged     = false;

// UI elements
Window        *s_main_window;
GFont          s_font_clock,
               s_font_date;
GBitmap       *s_icon_plugged;
TextLayer     *s_clock_layer,
              *s_date_layer;
Layer         *s_battery_layer;
BitmapLayer   *s_plugged_layer;
InverterLayer *s_inverter_layer;
