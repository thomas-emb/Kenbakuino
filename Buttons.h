#ifndef buttons_h
#define buttons_h

#include <Arduino.h>

// buttons/switches
// Abstract interface for reading the 15 (8 data, 7 control) push-buttons.
class Buttons
{
public:
  enum tButtons
  {
    eBit0,
    eBit1,
    eBit2,
    eBit3,
    eBit4,
    eBit5,
    eBit6,
    eBit7,

    eInputClear,
    eAddressDisplay,
    eAddressSet,
    eMemoryRead,
    eMemoryStore,
    eRunStart,
    eRunStop,
    eUnused
  };

  virtual ~Buttons() {}

  virtual void Init() = 0;
  virtual bool GetButtons(word& State, word& NewPressed, bool deBounce) = 0;
  virtual bool IsPressed(word BtnState, int Btn) = 0;
  virtual bool GetButtonDown(word BtnState, int& Btn) = 0;
};

extern Buttons& buttons;
#endif
