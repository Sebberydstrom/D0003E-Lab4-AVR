#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdbool.h>
#include <stdint.h>
#include "../TinyTimber.h"
#include "PGenerator.h"

typedef struct {
	Object super;
	uint8_t currently_selected;
	PGenerator* pgs[2];
	Msg temp_msg;
} Controller;

#define initController(pg0, pg1) { initObject(), 0, { pg0, pg1 }, 0, NULL }

int ctrl_set_active(Controller* self, int arg);

int ctrl_save_state(Controller* self, int arg);

int ctrl_increase_freq(Controller* self, int arg);

int ctrl_decrease_freq(Controller* self, int arg);

int ctrl_delayed_inc(Controller* self, int arg);

int ctrl_delayed_dec(Controller* self, int arg);

int ctrl_start(Controller* self, int arg);

int ctrl_reset(Controller* self, int arg);

#endif /* CONTROLLER_H_ */