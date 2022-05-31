#include "Controller.h"
#include "../lcd.h"
#include <avr/io.h>

// Both of these should be written to `LCDDR0`. It show the special symbols for which pulse generator that i chosen.
#define DISPLAY_ONE ((1 << 1) | (1 << 2))
#define DISPLAY_TWO ((1 << 5) | (1 << 6))

// Positions to print at for PulseGenerator 1 and 2.
#define POS_ONE 0
#define POS_TWO 4
#define GET_POS(s) ((s) == 0 ? POS_ONE : POS_TWO)

int ctrl_set_active(Controller* self, int arg) {
	self->currently_selected = arg;
	LCDDR0 = (LCDDR0 & ~SPECIAL_MASK) | (arg == 0 ? DISPLAY_ONE : DISPLAY_TWO);
	return 0;
}

int ctrl_save_state(Controller* self, __attribute__((unused)) int arg) {
	PGenerator* current = self->pgs[self->currently_selected];
	int freq = SYNC(current, pg_save_state, 0);
	
	printAt(freq, GET_POS(self->currently_selected));
	return 0;
}



int ctrl_increase_freq(Controller* self, __attribute__((unused)) int arg) {
	PGenerator* current = self->pgs[self->currently_selected];
	int freq = SYNC(current, pg_increase_freq, 1);
	
	printAt(freq, GET_POS(self->currently_selected));
	self->temp_msg = AFTER(SEC(1), self, ctrl_delayed_inc, arg);
	return 0;
}

int ctrl_decrease_freq(Controller* self, __attribute__((unused)) int arg) {
	PGenerator* current = self->pgs[self->currently_selected];
	int freq = SYNC(current, pg_decrease_freq, 1);
	
	printAt(freq, GET_POS(self->currently_selected));
	self->temp_msg = AFTER(SEC(1), self, ctrl_delayed_dec, arg);
	return 0;
}

int ctrl_delayed_inc(Controller* self, int arg) {
	if (self->temp_msg != NULL) {
		PGenerator* current = self->pgs[self->currently_selected];
		int freq = SYNC(current, pg_increase_freq, 1);
		printAt(freq, GET_POS(self->currently_selected));
		self->temp_msg = AFTER(MSEC(100), self, ctrl_delayed_inc, arg);
	}
	return 0;
}

int ctrl_delayed_dec(Controller* self, int arg) {
	if (self->temp_msg != NULL) {
		PGenerator* current = self->pgs[self->currently_selected];
		int freq = SYNC(current, pg_decrease_freq, 1);
		printAt(freq, GET_POS(self->currently_selected));
		self->temp_msg = AFTER(MSEC(100), self, ctrl_delayed_dec, arg);
	}
	return 0;
}

int ctrl_start(Controller* self, __attribute__((unused)) int arg) {
	ASYNC(self, ctrl_set_active, 0);
	printAt(0, POS_ONE);
	printAt(0, POS_TWO);
	return 0;
}

int ctrl_reset(Controller* self, __attribute__((unused)) int arg) {
	if(self->temp_msg) {
		ABORT(self->temp_msg);
		self->temp_msg = NULL;
	}
	return 0;
}