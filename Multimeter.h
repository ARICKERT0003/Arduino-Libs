#ifndef MULTIMETER
#define MULTIMETER 

#include <Arduino.h>
#include "SCPICommands.h"
#include "CSVData.h"
  
enum MM_ERROR
{
  NoError = 0,
  SerialWriteError = 1000
};

enum MM_MODE
{
  UNSET = -1,
  VoltageDC = 0,
  CurrentDC = 1
};

enum MM_COMMAND
{
  Restart = 0,
  Trigger = 1,
  Identify = 2,
  Fetch = 3,
  Function = 4
};

/** 
 *  @class Multimeter
 *  @brief Gets data from multimeter
 */  
class Multimeter : public SCPI
{
  public:

  struct MeterMode
  {
    char* mode;
    unsigned int len;
  };

  Multimeter();
  ~Multimeter();
  void init();
  int transmit(int);
  int receive(int);
  void receive();
  int execute(int);
  int execute(int, CSVData*, int);
  int validateMode(int);

  private:
  const int _timeOut = 300;
  unsigned long _baudRate;
  
  const int _bufferMax = 60;
  char _buffer[60];
  unsigned int _numBytes = 0;
  int _index;
  int _error;
  MeterMode _modeArray[3];
  scpiCommand _commandArray[6];
};

#endif
