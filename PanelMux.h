#ifndef panel_mux_h
#define panel_mux_h

#include <Arduino.h>

class PanelMux
{
public:
  static void Init();
  static void SelectBank(byte Bank);
  static byte ReadButtons(byte Bank);
  static void WriteLEDs(byte Bank, byte LEDMask6);

private:
  static bool m_Initialized;
};

#endif
