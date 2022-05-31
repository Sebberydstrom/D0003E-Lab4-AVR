#include "Joystick.h"

#include <avr/io.h>

/* Joystick connections.
   PB4: PCINT12 -- Press
   PB6: PCINT14 -- Up
   PB7: PCINT15 -- Down
   PE2: PCINT2  -- Left
   PE3: PCINT3  -- Right
*/

// Check if bit `b` in `p` is set to zero.
#define BIT_NOT_SET(p, b) ((((p) >> (b)) & 0x1) == 0)

int joystick_change_portb(Joystick* self, __attribute__((unused)) int arg) {
	uint8_t p = PINB;
	
	if (BIT_NOT_SET(p, PINB7)) {
		ASYNC(self->ctrl, ctrl_decrease_freq, 0); // Joystick down.
	} else if (BIT_NOT_SET(p, PINB6)) {
		ASYNC(self->ctrl, ctrl_increase_freq, 0); // Joystick up.
	} else if (BIT_NOT_SET(p, PINB4)) {
		ASYNC(self->ctrl, ctrl_save_state, 0); // Joystick pushed down.
	} else {
		ASYNC(self->ctrl, ctrl_reset, 0);
	}
	
	return 0;
}

int joystick_change_porte(Joystick* self, __attribute__((unused)) int arg) {
	uint8_t p = PINE;
	
	if (BIT_NOT_SET(p, PINE2)) {
		ASYNC(self->ctrl, ctrl_set_active, 0); // Joystick left.
	} else if (BIT_NOT_SET(p, PINE3)) {
		ASYNC(self->ctrl, ctrl_set_active, 1); // Joystick right.
	}
	
	return 0;
}
