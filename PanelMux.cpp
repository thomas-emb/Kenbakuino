#include <Arduino.h>
#include "PINS.h"
#include "PanelMux.h"

bool PanelMux::m_Initialized = false;

static const byte kButtonPins[8] =
{
  PIN_BTN_0,
  PIN_BTN_1,
  PIN_BTN_2,
  PIN_BTN_3,
  PIN_BTN_4,
  PIN_BTN_5,
  PIN_BTN_6,
  PIN_BTN_7
};

static const byte kLEDPins[6] =
{
  PIN_LED_0,
  PIN_LED_1,
  PIN_LED_2,
  PIN_LED_3,
  PIN_LED_4,
  PIN_LED_5
};

void PanelMux::Init()
{
  if (m_Initialized)
    return;

  pinMode(PIN_PANEL_SEL0, OUTPUT);
  pinMode(PIN_PANEL_SEL1, OUTPUT);

  for (byte i = 0; i < 8; i++)
  {
    pinMode(kButtonPins[i], INPUT);
  }

  for (byte i = 0; i < 6; i++)
  {
    pinMode(kLEDPins[i], OUTPUT);
    digitalWrite(kLEDPins[i], LOW);
  }

  SelectBank(0);
  m_Initialized = true;
}

void PanelMux::SelectBank(byte Bank)
{
  // Two independent select lines; only one should be active at a time.
  digitalWrite(PIN_PANEL_SEL0, Bank == 0 ? HIGH : LOW);
  digitalWrite(PIN_PANEL_SEL1, Bank == 1 ? HIGH : LOW);
}

byte PanelMux::ReadButtons(byte Bank)
{
  SelectBank(Bank);

  byte Value = 0;
  for (byte i = 0; i < 8; i++)
  {
    if (digitalRead(kButtonPins[i]))
    {
      bitSet(Value, i);
    }
  }
  return Value;
}

void PanelMux::WriteLEDs(byte Bank, byte LEDMask6)
{
  SelectBank(Bank);

  for (byte i = 0; i < 6; i++)
  {
    digitalWrite(kLEDPins[i], bitRead(LEDMask6, i) ? HIGH : LOW);
  }
}
