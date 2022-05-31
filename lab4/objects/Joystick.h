#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdbool.h>
#include <stdint.h>
#include "../TinyTimber.h"
#include "Controller.h"

typedef struct {
	Object super;
	Controller* ctrl;
	uint8_t marker;
} Joystick;

#define initJoystick(ctrl) { initObject(), ctrl, 0 }

int joystick_change_portb(Joystick* self, int _arg);
int joystick_change_porte(Joystick* self, int _arg);

#endif /* JOYSTICK_H_ */