#include "TimeHandler.h"  

volatile unsigned int TH_TIME_HOURS = 0;
volatile unsigned int TH_TIME_MICROSECONDS = 0;
volatile unsigned int TH_TIME_MILLISECONDS = 0;
volatile unsigned int TH_TIME_SECONDS = 0;
volatile unsigned int TH_TIME_MINUTES = 0;

TimeHandler::TimeHandler()
{}

void TimeHandler::init()
{
  Timer5.initialize(100);
  Timer5.attachInterrupt(callback,100);
  Timer5.stop();
  
  // Date-Time
  // 01234567
  // YYYYMMDD
  _ptrYear = &(_dateString[0]);
  _ptrMonth = _ptrYear+4;
  _ptrDay = _ptrYear+6;
  
  // Small-Time
  // 0123456789ABCDEF
  // HH:MM:SS:sss:uuu
  _ptrHr = &(_timeString[0]);      
  _ptrMin = _ptrHr+3;   
  _ptrSec = _ptrHr+6;   
  _ptrmSec = _ptrHr+9;
  _ptrmuSec = _ptrHr+13;

  resetTime();
}

void TimeHandler::callback()
{
  if(TH_TIME_MICROSECONDS < 900)
  { 
    TH_TIME_MICROSECONDS+=100;
    return;
  }
  TH_TIME_MICROSECONDS=0;
      
  if(TH_TIME_MILLISECONDS < 999)
  {
    TH_TIME_MILLISECONDS++;
    return;
  }
  TH_TIME_MILLISECONDS=0;
  
  if(TH_TIME_SECONDS < 59)
  {
    TH_TIME_SECONDS++;
    return;
  }
  TH_TIME_SECONDS=0;

  if(TH_TIME_MINUTES < 59)
  {
    TH_TIME_MINUTES++;
    return;
  }
  
  TH_TIME_HOURS++;
  TH_TIME_MINUTES=0;
}

void TimeHandler::resetTime()
{
  TH_TIME_MICROSECONDS = 0;
  TH_TIME_MILLISECONDS = 0;
  TH_TIME_SECONDS = 0;
  TH_TIME_MINUTES = 0;
  TH_TIME_HOURS = 0;
  
  _muSec = 0;
  _mSec = 0;
  _sec = 0;
  _min = 0;
  _hour = 0;
  
  memset( &(_timeString[0]), '0', sizeof(_timeString)-1 );
}

void TimeHandler::formatTimeString()
{
  char* temp;
  
  noInterrupts();
  _muSec = TH_TIME_MICROSECONDS;
  _mSec = TH_TIME_MILLISECONDS;
  _sec = TH_TIME_SECONDS;
  _min = TH_TIME_MINUTES;
  _hour = TH_TIME_HOURS;  
  interrupts();
  
  // Hours
  temp = _ptrHr;
  if(_hour < 10)
  {
    //Serial.println(_hours);
    (*temp) = '0';
    temp++;
    itoa(_hour, temp, 10);
    //Serial.println(_timeString);
  }
  else
  { itoa(_hour, _ptrHr, 10); }

  // Minutes
  temp = _ptrMin;
  if(_min < 10)
  {
    (*temp) = '0';
    temp++;
    itoa(_min, temp, 10);
  }
  else
  { itoa(_min, _ptrMin, 10); }

  // Seconds
  temp = _ptrSec;
  if(_sec < 10)
  {
    (*temp) = '0';
    temp++;
    itoa(_sec, temp, 10);
  }
  else
  { itoa(_sec, _ptrSec, 10); }

  // Milli-Seconds
  temp = _ptrmSec;
  if(_mSec < 100)
  {
    (*temp) = '0';
    temp++;
    if(_mSec < 10)
    {
      (*temp) = '0';
      temp++;
      itoa(_mSec, temp, 10);
    }
    else
    { itoa(_mSec, temp, 10); }
  }
  else
  { itoa(_mSec, _ptrmSec, 10); }
    
  // Micro-Seconds
  temp = _ptrmuSec;
  if(_muSec < 100)
  {
    (*temp) = '0';
    temp++;
    if(_muSec < 10)
    {
      (*temp) = '0';
      temp++; 
      itoa(_muSec, temp, 10);
    }
    else
    { itoa(_muSec, temp, 10); }
  }
  else
  { itoa(_muSec, _ptrmuSec, 10); }
  
  // 0123456789ABCDEF
  // HH:MM:SS:mmm:uuu
  _timeString[2]  = ':';
  _timeString[5]  = ':';
  _timeString[8]  = ':';
  _timeString[12] = ':';
}

void TimeHandler::setDate(int year, int month, int day)
{
  _year = year;
  _month = month;
  _day = day;
}

void TimeHandler::formatDateString()
{    
  itoa(_year, _ptrYear, 10);

  if(_month < 10)
  { 
    *_ptrMonth = '0';
    itoa(_month, _ptrMonth+1, 10); 
  }
  else
  {
    itoa(_month, _ptrMonth, 10);  
  }

  if(_day < 10)
  {
    *_ptrDay = '0';
    itoa(_day, _ptrDay+1, 10);
  }
  else
  {
    itoa(_day, _ptrDay, 10);  
  }

  _dateString[9] = '\0';
}

void TimeHandler::getDateString(char* dateString)
{
  formatDateString();  
  char temp[9] = "20200329\0";
  strcpy(dateString, temp);
}

unsigned int TimeHandler::getMinutes()
{ return (_hour*60) + _min; }

unsigned int TimeHandler::getHours()
{ return _hour; }

void TimeHandler::getTimeString(CSVData* ptrCSVData)
{
  formatTimeString();  
  //Serial.println(_timeString);
  ptrCSVData->setValue(_timeString, _timeStringLen, false);
}

void TimeHandler::printDateString()
{ 
  formatDateString();
  Serial.println(_dateString); 
}

void TimeHandler::printTimeString()
{
  formatTimeString();
  Serial.println(_timeString);
}

void TimeHandler::start()
{ 
  resetTime();
  Timer5.start(); 
}

void TimeHandler::stop()
{ Timer5.stop(); }
