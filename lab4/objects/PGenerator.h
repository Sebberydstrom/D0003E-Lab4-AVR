#ifndef PGENERATOR_H_
#define PGENERATOR_H_

#include <stdbool.h>
#include <stdint.h>
#include "../TinyTimber.h"
#include "SignalWriter.h"

#define DEFAULT_FREQ 0

typedef struct {
	Object super;
	uint8_t freq;
	uint8_t saved_freq;
	uint8_t write_mask;
	SignalWriter* writer;
} PGenerator;

#define initPulseGenerator(write_mask, writer) { initObject(), DEFAULT_FREQ, 0, write_mask, writer }

// Increase the hz for the currently selected pulse generator.
int pg_increase_freq(PGenerator* self, int arg);

// Decrease the hz for the currently selected pulse generator.
int pg_decrease_freq(PGenerator* self, int arg);

// Saves the frequency for the current pulse generator and sets it to zero. TODO: zero?
int pg_save_state(PGenerator* self, int arg);

int pg_update(PGenerator* self, int arg);

#endif /* PGENERATOR_H_ */