#ifndef SCPICOMMANDS
#define SCPICOMMANDS 

#include <Arduino.h>

class SCPI
{
  public:
   
  struct scpiCommand
  {
    byte* cmd;
    unsigned int len;
    char response[44];
    unsigned int responseLen;
  };

  // Command
  const char restartCmd[6] = {'*','R','S','T',0x0D};
  const unsigned int restartLen = 5;

  const char triggerCmd[6] = {'*','T','R','G',0x0D};
  const unsigned int triggerLen = 5;
      
  const char identifyCmd[7] = {'*','I','D','N','?',0x0D};
  const unsigned int identifyLen = 6;
  
  //static const char fetchCmd[] = {':','F','E','T','C','?',0x0D};
  const char fetchCmd[8] = {':','f','e','t','c','?',0x0D};
  const unsigned int fetchLen = 7;
  
  const char functionCmd[8] = {':','F','U','N','C','?',0x0D};
  const unsigned int functionLen = 7;

  // Mode
  const char modeVoltDC[8] = {'v','o','l','t',':','d','c'};
  const unsigned int modeVoltDCLen = 7;
  
  const char modeCurrDC[8] = {'c','u','r','r',':','d','c'};
  const unsigned int modeCurrDCLen = 7;
};

#endif
