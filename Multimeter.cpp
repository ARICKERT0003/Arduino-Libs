#include "Multimeter.h"  

Multimeter::Multimeter()
{}

Multimeter::~Multimeter()
{}

void Multimeter::init()
{ 
  // Initailize command array
  _commandArray[Restart].cmd = restartCmd;
  _commandArray[Restart].len = restartLen;
  
  _commandArray[Trigger].cmd = triggerCmd;
  _commandArray[Trigger].len = triggerLen;

  _commandArray[Identify].cmd = identifyCmd;
  _commandArray[Identify].len = identifyLen;
  
  _commandArray[Fetch].cmd = fetchCmd;
  _commandArray[Fetch].len = fetchLen;
  
  _commandArray[Function].cmd = functionCmd;
  _commandArray[Function].len = functionLen;

  // Initialize function array
  _modeArray[VoltageDC].mode = modeVoltDC;
  _modeArray[VoltageDC].len = modeVoltDCLen;

  _modeArray[CurrentDC].mode = modeCurrDC;
  _modeArray[CurrentDC].len = modeCurrDCLen;
}

int Multimeter::transmit(int cmdIndex)
{
  size_t writeLen = 0;
  writeLen = Serial1.write(_commandArray[cmdIndex].cmd, _commandArray[cmdIndex].len);
  if(writeLen != _commandArray[cmdIndex].len)
  { return SerialWriteError; }

  return NoError;
}

int Multimeter::receive(int cmdIndex)
{
  size_t numBytes = 0;

  // Get response from meter
  _numBytes = Serial1.readBytesUntil(0x0D, _buffer, _bufferMax);
  _commandArray[cmdIndex].responseLen = _numBytes;

  // Copy buffer into response
  memcpy(_commandArray[cmdIndex].response, _buffer, _numBytes);

  // Add terminating character
  _commandArray[cmdIndex].response[_numBytes] = '\0';

  return NoError;
}

void Multimeter::receive()
{
  // Get response from meter
  _numBytes = Serial1.readBytesUntil(0x0D, _buffer, _bufferMax);
}

int Multimeter::execute(int cmdIndex)
{
  _error = transmit(cmdIndex);
  if( _error )
  { return _error; }

  _error = receive(cmdIndex);
  if( _error )
  { return _error; }

  return NoError;
}

int Multimeter::execute(int cmdIndex, CSVData* ptrCSVData, int testMode)
{
  _error = transmit(cmdIndex);
  if( _error )
  { return _error; }

  receive();

  ptrCSVData->setValue(_buffer, _numBytes, true);
  
  return NoError;
}

int Multimeter::validateMode(int mode)
{
/*
  _error = execute(MM_COMMAND::Function);
  if( _error )
  { return _error; }


  if( _commandArray[Command::Function].responseLen != Response::functionLen )
  { 
    _mode = UNSET;
    return IncorrectMode; 
  }
   
  // Check that chars match
  for( int i=0; i<_commandArray[Command::Function].responseLen; i++ )
  {
    if(_commandArray[Command::Function].response[i] != _functionArray[VoltageDC].func[i])
    {
      
    }
  }
   
  return NoError;
*/
}

/*
int Multimeter::getDataPoint(DataPoint& dataPoint)
{
  switch( _mode )
  {
    case VoltageDC:
      _error = execute(MeterCodes::Fetch);
      if( _error )
      { return _error; }

      
          
    break;

    case CurrentDC:
    break;

    default:
    return IncorrectMode;
  }
} 
*/    
