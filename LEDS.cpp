#include "PINS.h"
#include "LEDS.h"
#include "ShiftRegisterLEDs.h"
#include "MatrixLEDs.h"

#if defined(USE_MATRIX_FRONT_PANEL) && USE_MATRIX_FRONT_PANEL
#define ACTIVE_LEDS_MATRIX 1
#else
#define ACTIVE_LEDS_MATRIX 0
#endif

static ShiftRegisterLEDs g_shiftRegisterLEDs;
static MatrixLEDs g_matrixLEDs;

#if ACTIVE_LEDS_MATRIX
LEDs& leds = g_matrixLEDs;
#else
LEDs& leds = g_shiftRegisterLEDs;
#endif
