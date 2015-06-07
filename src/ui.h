#pragma once

#include "fields.h"

void update_inversion()
{
	if (!persist_exists(KEY_INVERT))
		persist_write_bool(KEY_INVERT, false);

	bool invert = persist_read_bool(KEY_INVERT);
	layer_set_hidden((Layer *)s_inverter_layer, !invert);
}

void update_ui()
{
  // update ui elements
	update_inversion();

  // flash the backlight to alert that we've updated
	light_enable_interaction();
}
