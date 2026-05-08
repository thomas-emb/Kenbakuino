#include "PINS.h"
#include "Buttons.h"
#include "ShiftRegisterButtons.h"
#include "MatrixButtons.h"

#if defined(USE_MATRIX_FRONT_PANEL) && USE_MATRIX_FRONT_PANEL
#define ACTIVE_BUTTONS_MATRIX 1
#else
#define ACTIVE_BUTTONS_MATRIX 0
#endif

static ShiftRegisterButtons g_shiftRegisterButtons;
static MatrixButtons g_matrixButtons;

#if ACTIVE_BUTTONS_MATRIX
Buttons& buttons = g_matrixButtons;
#else
Buttons& buttons = g_shiftRegisterButtons;
#endif
