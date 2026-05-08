#ifndef shift_register_leds_h
#define shift_register_leds_h

#include "LEDS.h"

// Shift-register implementation: 74HC595 for data LEDs + direct control LEDs.
class ShiftRegisterLEDs : public LEDs
{
public:
  virtual void Init();
  virtual void Display(byte Data, byte Control);

private:
  void ShiftOut(byte LEDs);

  static byte m_pDirectControlPins[];
  byte m_LastData;
  byte m_LastControl;
};

#endif
