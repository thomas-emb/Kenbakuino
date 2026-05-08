#ifndef leds_h
#define leds_h

#include <Arduino.h>
 
// Abstract interface for controlling the 12 front-panel LEDs.

class LEDs
{
public:
  virtual ~LEDs() {}

  virtual void Init() = 0;
  virtual void Display(byte Data, byte Control) = 0;
};

extern LEDs& leds;
#endif
