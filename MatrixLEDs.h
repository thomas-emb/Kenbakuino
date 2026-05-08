#ifndef matrix_leds_h
#define matrix_leds_h

#include "LEDS.h"

// Matrix implementation: two banks with shared LED lines.
class MatrixLEDs : public LEDs
{
public:
  virtual void Init();
  virtual void Display(byte Data, byte Control);

private:
  void Refresh();

  byte m_LastData;
  byte m_LastControl;
};

#endif
