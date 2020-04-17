#ifndef PINEVENT
#define PINEVENT

#include <Arduino.h>
#include <Servo.h>
#include <TimerThree.h>
#include <TimerFive.h>

class PinEvent
{
  public:
  PinEvent();
  PinEvent(byte, unsigned long);
  void init(byte, unsigned long);
  void setPin(byte);
  void setPin(byte, bool);
  void setDuration(unsigned long);
  void trigger();

  protected:
  byte _pin;
  volatile unsigned long _duration; // sec  
  bool _pinState;  
};

class TimerPWM : public PinEvent
{
  public:
  TimerPWM();
  TimerPWM(byte, unsigned long, unsigned int);
  void init(byte, unsigned long, unsigned int);
  void setPeriod(unsigned long);
  void setDuty(unsigned int);
  void start();
  void stop();

  private:
  unsigned int _duty;
  unsigned long _period;
};

class PinEventInterrupt : public PinEvent
{
  public:
  PinEventInterrupt();
  PinEventInterrupt(byte, unsigned long, void*);
  PinEventInterrupt(byte, bool, unsigned long, unsigned long);
  void init(byte, bool, unsigned long, unsigned long);
  void setGlobals(byte, unsigned long, unsigned long);
  void setISR( void* );
  static void pwmISR();
  void start();
  void stop();
  unsigned long getCount();
  void printEverything();

  private:
  bool activeState;
};

class TimedServo : public PinEvent
{
  public:
  TimedServo();
  void init(byte, int);
  void attachServo(byte pin);
  void setISR( void*);
  void setSweep(unsigned long, unsigned long, int, int);
  static void timedSweep();
  void start(int);
  void stop(int);
};
#endif
