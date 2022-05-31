#include <avr/io.h>
#include "TinyTimber.h"
#include "lcd.h"
#include "objects/Joystick.h"
#include "objects/PGenerator.h"
#include "objects/Controller.h"
#include "objects/SignalWriter.h"


void init_joyst() {
	PORTB = PORTB | (1 << PB7) | (1 << PB6) | (1 << PB4);
	PORTE = PORTE | (1 << PE3) | (1 << PE2);
	// Setup external interrupts.
	EIMSK  = (1 << PCIE1) | (1 << PCIE0);
	// Register that is connected to the joystick for generating interrupts.
	// PB6 is for example connected to Pin Change Interrupt 14 = PCINT14, means that PB6 can serve as 
	// an external interrupt source.
	PCMSK1 = (1 << PCINT15) | (1 << PCINT14) | (1 << PCINT12);
	PCMSK0 = (1 << PCINT2) | (1 << PCINT3);
}

static SignalWriter sw = initWriter();
// The first PGenerator writes the output to bit 4 of port E.
static PGenerator pg0 = initPulseGenerator(1 << PE4, &sw);
// The second PGenerator writes the output to bit 6 of port E.
static PGenerator pg1 = initPulseGenerator(1 << PE6, &sw);
static Controller ctrl = initController(&pg0, &pg1);
// Setup joystick with the pulse generators.
static Joystick js = initJoystick(&ctrl);

int main(void) {
	init_lcd();
	init_joyst();
	clear();
	
	INSTALL(&js, joystick_change_porte, IRQ_PCINT0);
	INSTALL(&js, joystick_change_portb, IRQ_PCINT1);
	
	return TINYTIMBER(&ctrl, ctrl_start, 0);
}

