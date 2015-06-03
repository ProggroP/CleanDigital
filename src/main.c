#include <pebble.h>
#include "date_time_utils.h"
#include "battery_utils.h"

#define CLOCK_FONT_ID  RESOURCE_ID_FONT_CLOCK_54
#define DATE_FONT_ID   RESOURCE_ID_FONT_MONTH_28

enum {
	KEY_INVERT = 0x0
};

	
// functions

static void init();
static void deinit();
static void load_resources();
static void unload_resources();
static void main_window_load(Window *w);
static void main_window_unload(Window *w);

void update_inversion();

static void tick_handler(struct tm *tick_time, TimeUnits units_changed);
static void battery_handler(BatteryChargeState charge_state);
static void in_recv_handler(DictionaryIterator *it, void *ctx);


// fields

struct tm *s_tick_time;
Window *s_main_window;
GFont s_font_clock, s_font_date;
TextLayer *s_clock_layer, *s_date_layer;
Layer *s_battery_layer;
InverterLayer *s_inverter_layer;
int s_battery_pct = 0;


// function definitions

static void init_local_storage()
{
	if (!persist_exists(KEY_INVERT))
	{
		APP_LOG(APP_LOG_LEVEL_DEBUG_VERBOSE, "No value for KEY_INVERT, defaulting to false");
		persist_write_bool(KEY_INVERT, false);
	}
}

void init()
{
	time_t temp = time(NULL);				// we keep tick_time as a static field for memory purposes
	s_tick_time = localtime(&temp);	// (to be able to free the struct tm on deinit)
	
	init_local_storage();
	load_resources();
	
	s_main_window = window_create();
	window_set_background_color(s_main_window, GColorBlack);
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load   = main_window_load,
		.unload = main_window_unload
	});
	window_stack_push(s_main_window, true);
	
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	battery_state_service_subscribe(battery_handler);
	
	app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

void deinit()
{
	unload_resources();
	window_destroy(s_main_window);
	
	free(s_tick_time);
}


void load_resources()
{
	s_font_clock = fonts_load_custom_font(resource_get_handle(CLOCK_FONT_ID));
	s_font_date  = fonts_load_custom_font(resource_get_handle(DATE_FONT_ID));
}

void unload_resources()
{
	fonts_unload_custom_font(s_font_clock);
	fonts_unload_custom_font(s_font_date);
}

void main_window_load(Window *w)
{
	s_clock_layer = text_layer_create(GRect(0, 34, 144, 65));
	text_layer_set_background_color(s_clock_layer, GColorClear);
	text_layer_set_text_color(s_clock_layer, GColorWhite);
	text_layer_set_text_alignment(s_clock_layer, GTextAlignmentCenter);
	text_layer_set_font(s_clock_layer, s_font_clock);
	layer_add_child(window_get_root_layer(w), text_layer_get_layer(s_clock_layer));
	
	s_battery_layer = layer_create(GRect(0, 0, 144, 168));
	layer_set_update_proc(s_battery_layer, update_battery_proc);
	layer_add_child(window_get_root_layer(w), s_battery_layer);
	
	
	s_date_layer = text_layer_create(GRect(0, 105, 130, 50));
	text_layer_set_background_color(s_date_layer, GColorClear);
	text_layer_set_text_color(s_date_layer, GColorWhite);
	text_layer_set_text_alignment(s_date_layer, GTextAlignmentRight);
	text_layer_set_font(s_date_layer, s_font_date);
	layer_add_child(window_get_root_layer(w), text_layer_get_layer(s_date_layer));
	
	s_inverter_layer = inverter_layer_create(GRect(0, 0, 144, 168));
	layer_add_child(window_get_root_layer(w), inverter_layer_get_layer(s_inverter_layer));
	
	update_time(s_clock_layer, s_tick_time);
	update_date(s_date_layer, s_tick_time);
	update_inversion();
}

void main_window_unload(Window *w)
{
	layer_destroy(s_battery_layer);
	text_layer_destroy(s_clock_layer);
	text_layer_destroy(s_date_layer);
	layer_destroy((Layer *)s_inverter_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
	s_tick_time = tick_time;
	update_time(s_clock_layer, s_tick_time);
	update_date(s_date_layer, s_tick_time);
}

static void battery_handler(BatteryChargeState charge_state)
{
	update_battery(s_battery_layer);
}

void update_inversion()
{
	if (!persist_exists(0))
		persist_write_bool(0, false);
	
	bool invert = persist_read_bool(0);
	layer_set_hidden((Layer *)s_inverter_layer, !invert);
}

static void in_recv_handler(DictionaryIterator *it, void *ctx)
{
	Tuple *invert_tuple = dict_find(it, KEY_INVERT);
	bool invert = strcmp(invert_tuple->value->cstring, "true") == 0;
	
	persist_write_bool(KEY_INVERT, invert);
	update_inversion();
}



int main(void)
{
	init();
	app_event_loop();
	deinit();
}