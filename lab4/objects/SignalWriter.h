#ifndef SIGNALWRITER_H_
#define SIGNALWRITER_H_

#include "../TinyTimber.h"

typedef struct {
	Object super;
} SignalWriter;

#define initWriter() { initObject() }

int write(SignalWriter* self, int arg);

int write_zero(SignalWriter* self, int mask);

#endif /* SIGNALWRITER_H_ */