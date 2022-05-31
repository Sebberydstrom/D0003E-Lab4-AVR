#include "PGenerator.h"

#define MAX_FREQ 99

int pg_increase_freq(PGenerator* self, __attribute__((unused)) int arg) {
	if (self->freq == 0) {
		// If freq = 0, start it!
		ASYNC(self, pg_update, 0);
	}
	
	if (self->freq + 1 <= MAX_FREQ) {
		self->freq += 1;
	}
	return self->freq;
}

int pg_decrease_freq(PGenerator* self, __attribute__((unused)) int arg) {
	if (self->freq == 1) {
		ASYNC(self->writer, write_zero, self->write_mask);
	}
	if (self->freq != 0) {
		self->freq -= 1;
	}
	
	return self->freq;
}

int pg_save_state(PGenerator* self, __attribute__((unused)) int arg) {
	if (self->freq == 0) {
		self->freq = self->saved_freq;
		self->saved_freq = 0;
		ASYNC(self, pg_update, 0);
		} else {
		self->saved_freq = self->freq;
		self->freq = DEFAULT_FREQ;
		ASYNC(self->writer, write_zero, self->write_mask);
	}
	return self->freq;
}

int pg_update(PGenerator* self, __attribute__((unused)) int arg) {
	if (self->freq != 0) {
		ASYNC(self->writer, write, self->write_mask);

		uint32_t delay = 1000000 / self->freq;
		AFTER(USEC(delay / 2), self, pg_update, 0);
	}
	return 0;
}