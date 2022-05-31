#include "SignalWriter.h"
#include <avr/io.h>

int write(__attribute__((unused)) SignalWriter* self, int mask) {
	PORTE = PORTE ^ mask;
	return 0;
}

int write_zero(__attribute__((unused)) SignalWriter* self, int mask) {
	PORTE = PORTE & ~mask;
	return 0;
}
