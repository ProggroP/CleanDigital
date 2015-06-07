#pragma once

#include "fields.h"
#include "ui.h"

static void in_recv_handler(DictionaryIterator *it, void *ctx)
{
	Tuple *invert_tuple = dict_find(it, KEY_INVERT);
	bool invert = strcmp(invert_tuple->value->cstring, "true") == 0;

	// update persistent values and reload ui
	persist_write_bool(KEY_INVERT, invert);
	update_ui();
}
