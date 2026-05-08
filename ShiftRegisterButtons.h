#ifndef shift_register_buttons_h
#define shift_register_buttons_h

#include "Buttons.h"

// Shift-register implementation (74HC165 x2).
class ShiftRegisterButtons : public Buttons
{
public:
  virtual void Init();
  virtual bool GetButtons(word& State, word& NewPressed, bool deBounce);
  virtual bool IsPressed(word BtnState, int Btn);
  virtual bool GetButtonDown(word BtnState, int& Btn);

private:
  word ShiftIn(int LatchPin, int DataPin, int ClockPin, int BitOrder);
  static byte m_pMap[];
  word m_wPrevState;
};

#endif
