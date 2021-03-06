#pragma once

/*
 *	ui.h
 * 		Contains functions used to update the user interface
 */

#include "fields.h"

bool s_was_plugged  = false;
bool s_was_inverted = false;

// alert the user to changes by vibrating and lighting up
void alert_changes()
{
	light_enable_interaction();
	vibes_short_pulse();
}

void update_inversion()
{
	if (!persist_exists(KEY_INVERT))
		persist_write_bool(KEY_INVERT, false);

	bool invert = persist_read_bool(KEY_INVERT);
	layer_set_hidden((Layer *)s_inverter_layer, !invert);

	// flash backlight if state has changed
	if (invert != s_was_inverted)
		alert_changes();

	s_was_inverted = invert;
}

void update_battery()
{
	layer_mark_dirty(s_battery_layer);
}

void update_plugged()
{
	s_plugged = battery_state_service_peek().is_plugged;

	// hide if not plugged in
	layer_set_hidden((Layer *)s_plugged_layer, !s_plugged);

	// flash backlight if state has changed
	if (s_plugged != s_was_plugged)
		alert_changes();

	s_was_plugged = s_plugged;
}

void update_ui()
{
  // update ui elements
	update_inversion();
	update_plugged();
}
