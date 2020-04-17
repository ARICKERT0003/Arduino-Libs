#ifndef TIMEHANDLER
#define TIMEHANDLER

#include <Arduino.h>
#include <TimerFive.h>
#include "CSVData.h"

// ~300-400 mus per 
class TimeHandler
{
  public:
  //char dateString[9];

  TimeHandler();
  void init();
  static void callback();
  void setDate(int, int, int);
  unsigned int getMinutes();
  unsigned int getHours();
  void getTimeString(CSVData*);
  void getDateString(char*);
  void printDateString();
  void printTimeString();
  void start();
  void stop();

  private:
  char _dateString[9];
  char* _ptrYear;
  char* _ptrMonth;
  char* _ptrDay;
  int _year;
  int _month;
  int _day;

  // 123456789ABCDEFG
  // HH:MM:SS:mmm:uuu
  char _timeString[17];
  char* _ptrHr;
  char* _ptrMin;
  char* _ptrSec;
  char* _ptrmSec;
  char* _ptrmuSec; 
  const uint8_t _timeStringLen = 17;
  unsigned int _muSec;
  unsigned int _mSec;
  unsigned int _sec;
  unsigned int _min;
  unsigned int _hour;  

  void formatDateString();
  void formatTimeString();
  void resetTime();
};

#endif
