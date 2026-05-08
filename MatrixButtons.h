#ifndef matrix_buttons_h
#define matrix_buttons_h

#include "Buttons.h"

// Matrix front-panel implementation (two banks, shared IO lines).
class MatrixButtons : public Buttons
{
public:
  virtual void Init();
  virtual bool GetButtons(word& State, word& NewPressed, bool deBounce);
  virtual bool IsPressed(word BtnState, int Btn);
  virtual bool GetButtonDown(word BtnState, int& Btn);

private:
  word ReadMatrixState();
  static byte m_pMap[];
  word m_wPrevState;
};

#endif
