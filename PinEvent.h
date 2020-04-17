/** 
 *  @file    PinEvent.h 
 *  @author  Alex Rickert
 *  @date    04/02/2020
 *  @version 1.0
 */

#ifndef PINEVENT
#define PINEVENT

#include <Arduino.h>
#include <Servo.h>
#include <TimerThree.h>
#include <TimerFive.h>

/**
 *  @class PinEvent
 *  @brief General class for pin interaction 
 */
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

/**
 *  @class TimerPWM
 *  @brief Wrapper for PWM functionality on Timer3
 */
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

/**
 *  @class   PinEventInterrupt
 *  @brief   Wrapper for ISR functionality on Timer3
 *  @details Specifically tailored for PWM which exceeds the max period of the
 *           built in PWM functionality
 */
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

/**
 *  @class  TimedServo
 *  @brief  Extends Timer3 ISR functionality to trigger servo movement
 */
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
