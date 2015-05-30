#include <pebble.h>

#define TIME_BUFFER "00:00"
#define TIME_FMT_24 "%H:%M"
#define TIME_FMT_12 "%I:%M"
#define DATE_BUFFER "00 Mth"
#define DATE_FORMAT "%e %b"

static void update_time(TextLayer *this_layer, struct tm *tick_time)
{
	static char buffer[] = TIME_BUFFER;
	strftime(buffer, sizeof(TIME_BUFFER),
			 ((clock_is_24h_style() == true) ? TIME_FMT_24 : TIME_FMT_12), tick_time);
	text_layer_set_text(this_layer, buffer);
}

static void update_date(TextLayer *this_layer, struct tm *tick_time)
{
	static char buffer[] = DATE_BUFFER;
	strftime(buffer, sizeof(DATE_BUFFER), DATE_FORMAT, tick_time);
	text_layer_set_text(this_layer, buffer);
}