#include <Arduino.h>
#include "MCP.h"
#include "MatrixLEDs.h"
#include "PanelMux.h"

void MatrixLEDs::Init()
{
  PanelMux::Init();

  m_LastData = 0;
  m_LastControl = 0;
  Refresh();
}

void MatrixLEDs::Refresh()
{
  // Bank 0 carries data LEDs bit0..bit5.
  byte Bank0 = 0;
  bitWrite(Bank0, 0, bitRead(m_LastData, 0));
  bitWrite(Bank0, 1, bitRead(m_LastData, 1));
  bitWrite(Bank0, 2, bitRead(m_LastData, 2));
  bitWrite(Bank0, 3, bitRead(m_LastData, 3));
  bitWrite(Bank0, 4, bitRead(m_LastData, 4));
  bitWrite(Bank0, 5, bitRead(m_LastData, 5));

  // Bank 1 carries data bit6..bit7 and control LEDs INP/ADDR/MEM/RUN.
  byte Bank1 = 0;
  bitWrite(Bank1, 0, bitRead(m_LastData, 6));
  bitWrite(Bank1, 1, bitRead(m_LastData, 7));
  bitWrite(Bank1, 2, bitRead(m_LastControl, MCP::eInput));
  bitWrite(Bank1, 3, bitRead(m_LastControl, MCP::eAddress));
  bitWrite(Bank1, 4, bitRead(m_LastControl, MCP::eMemory));
  bitWrite(Bank1, 5, bitRead(m_LastControl, MCP::eRun));

  PanelMux::WriteLEDs(0, Bank0);
  PanelMux::WriteLEDs(1, Bank1);
}

void MatrixLEDs::Display(byte Data, byte Control)
{
  if (Data != m_LastData || Control != m_LastControl)
  {
    m_LastData = Data;
    m_LastControl = Control;
  }

  // Always refresh so multiplexed LEDs stay active.
  Refresh();
}
