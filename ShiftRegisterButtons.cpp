#include <Arduino.h>
#include "PINS.h"
#include "ShiftRegisterButtons.h"

byte ShiftRegisterButtons::m_pMap[] = // eg logical eBit2 is actually bit6 from the 165
{
  0, 1, 6, 7, 4, 5, 2, 3,
  11, 12, 13, 14, 15, 9, 8, 10
};

void ShiftRegisterButtons::Init()
{
  // prepare the pins which talk to the 165
  pinMode(PIN_BTN_PL, OUTPUT);
  pinMode(PIN_BTN_CP, OUTPUT);
  pinMode(PIN_BTN_Q7, INPUT);

  m_wPrevState = 0xFFFF;
}

word ShiftRegisterButtons::ShiftIn(int LatchPin, int DataPin, int ClockPin, int BitOrder)
{
  // read 16 bits of button statuses
  digitalWrite(ClockPin, HIGH);

  digitalWrite(LatchPin, LOW);
  digitalWrite(LatchPin, HIGH);

  byte First = shiftIn(DataPin, ClockPin, BitOrder);
  byte Second = shiftIn(DataPin, ClockPin, BitOrder);
  return word(Second, First);
}

bool ShiftRegisterButtons::GetButtons(word& State, word& NewPressed, bool Wait)
{
  word ThisState = ShiftIn(PIN_BTN_PL, PIN_BTN_Q7, PIN_BTN_CP, MSBFIRST);

  if (Wait)
  {
    delay(20);
    word DebouncedState = ShiftIn(PIN_BTN_PL, PIN_BTN_Q7, PIN_BTN_CP, MSBFIRST);
    if (DebouncedState != ThisState)
      return false;
  }

  if (ThisState != m_wPrevState)
  {
    NewPressed = ThisState & (~m_wPrevState);

    m_wPrevState = ThisState;
    State = ThisState;
    return true;
  }
  return false;
}

bool ShiftRegisterButtons::IsPressed(word BtnState, int Btn)
{
  return bitRead(BtnState, m_pMap[Btn]);
}

bool ShiftRegisterButtons::GetButtonDown(word BtnState, int& Btn)
{
  for (Btn = eBit0; Btn <= eUnused; Btn++)
  {
    if (IsPressed(BtnState, Btn))
      return true;
  }
  return false;
}
