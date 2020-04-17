/** 
 *  @file    Multimeter.h 
 *  @author  Alex Rickert
 *  @date    04/02/2020
 *  @version 1.0
 */

#ifndef MULTIMETER
#define MULTIMETER 

#include <Arduino.h>
#include "SCPICommands.h"
#include "CSVData.h"

/**
 *  @enum  MM_ERROR
 *  @brief Error codes for multimeter
 *  @var   NoError
 *  @var   SerialWriteError
 */
enum MM_ERROR
{
  NoError = 0,
  SerialWriteError = 1000
};

/**
 *  @enum  MM_MODE
 *  @brief Modes for multimeter
 *  @var   VoltageDC
 *  @var   CurrentDC
 */
enum MM_MODE
{
  UNSET = -1,
  VoltageDC = 0,
  CurrentDC = 1
};

/**
 *  @enum  MM_COMMAND
 *  @brief Commands for multimeter 
 *  @var   Restart  
 *         Restart the multimeter
 *  @var   Trigger  
 *         Forces multimeter to capture new value
 *  @var   Identify 
 *         Returns multimeter information
 *  @var   Fetch    
 *         Returns last data point multimater captured
 *  @var   Function 
 *         Returns mode multimeter is in (ie VoltageDC, VoltageAC, CurrentDC,
 *         ..)
 */
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
 *  @brief Gets data from multimeter via SCPI protocol\n
 *         This is tailored to BK Precision 5491B Multimeter
 */  
class Multimeter : public SCPI
{
  public:

  /**
   *  @struct MeterMode
   *  @brief  Contains strings to compare and validate meter mode
   */
  struct MeterMode
  {
    char* mode;
    unsigned int len;
  };

  /**
   *  @fn    Multimeter
   *  @brief Empty constructor
   */
  Multimeter();

  /**
   *  @fn    ~Multimeter
   *  @brief Empty destructor
   */
  ~Multimeter();

  /**
   *  @fn    init
   *  @brief Initializes arrays with apropriate commands and modes 
   */
  void init();

  /**
   *  @fn    transmit
   *  @brief Sends command to multimeter
   *  @param Command @ref MM_COMMAND
   */
  int transmit(int);

  /**
   *  @fn    receive
   *  @brief Waits for response from multimeter and stores in 
   *         command specfic buffer
   *  @param Command @ref MM_COMMAND
   */
  int receive(int);

  /**
   *  @fn    receive
   *  @brief Waits for response from multimeter and stores in 
   *         general buffer
   */
  void receive();

  /**
   *  @fn    execute
   *  @brief Sends command and waits for response. Stores response in
   *         command specific buffer
   */
  int execute(int);

  /**
   *  @fn    execute
   *  @brief Sends command, waits for response, stores response in
   *         CSVData instance
   *  @param Command @ref MM_COMMAND
   *  @param ptrCSVData @ref CSVDATA
   *  @param @deprecated meterMode
   */
  int execute(int, CSVData*, int);

  /**
   *  @fn    validateMode
   *  @brief NOT FUNCTIONAL YET
   */
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
