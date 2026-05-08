#include <Arduino.h>
#include "MatrixButtons.h"
#include "PanelMux.h"

byte MatrixButtons::m_pMap[] = // direct map for banked matrix scan slots
{
  0, 1, 2, 3, 4, 5, 6, 7,
  8, 9, 10, 11, 12, 13, 14, 15
};

void MatrixButtons::Init()
{
  PanelMux::Init();

  // set no prev state
  m_wPrevState = 0xFFFF;
}

word MatrixButtons::ReadMatrixState()
{
  // 16 logical slots: bank0(8 switches) + bank1(8 switches)
  byte Bank0 = PanelMux::ReadButtons(0);
  byte Bank1 = PanelMux::ReadButtons(1);
  return word(Bank1, Bank0);
}

bool MatrixButtons::GetButtons(word& State, word& NewPressed, bool Wait)
{
  // get the current raw state and any that have changed to down
  word ThisState = ReadMatrixState();
  
  if (Wait)
  {
    // simple de-bounce, if requested
    delay(20);
    word DebouncedState = ReadMatrixState();
    if (DebouncedState != ThisState)
      return false;
  }
  
  if (ThisState != m_wPrevState)
  {
    NewPressed = ThisState & (~m_wPrevState);  // only those that have *changed* from OFF to ON, i.e. DOWN

    m_wPrevState = ThisState;
    State = ThisState;
    return true;
  }
  return false;
}

bool MatrixButtons::IsPressed(word BtnState, int Btn)
{
  // is the Btn down (in the given state)
  return bitRead(BtnState, m_pMap[Btn]);
}

bool MatrixButtons::GetButtonDown(word BtnState, int& Btn)
{
  // return the first Btn down in the state
  for (Btn = eBit0; Btn <= eUnused; Btn++)
  {
    if (IsPressed(BtnState, Btn))
      return true;
  }
  return false;
}
