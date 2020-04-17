#include "PinEvent.h"

// Pin Event Interrupt Variables
byte PE_PIN = 2;
unsigned long PE_TIMER_RESOLUTION = 1000000; // 1 second
unsigned long PE_PERIOD = 0;                        
unsigned long PE_DUTY_START = 0;
unsigned long PE_COUNTER = 0;  

// =============================================
// PinEvent
// =============================================
PinEvent::PinEvent()
{}

PinEvent::PinEvent(byte pin, unsigned long duration)
{ init(pin, duration); }

void PinEvent::init(byte pin, unsigned long duration)
{
  setPin(pin);
  setDuration(duration); 
}

void PinEvent::setPin(byte pin)
{ 
  _pin = pin; 
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
}

void PinEvent::setPin(byte pin, bool value)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, value);
}

void PinEvent::setDuration(unsigned long duration)
{ _duration = duration; }

void PinEvent::trigger()
{
  digitalWrite(_pin, LOW);
  delay(_duration*1000);
  digitalWrite(_pin, HIGH);
}

// =============================================
// TimerPWM
// =============================================
TimerPWM::TimerPWM()
{}

TimerPWM::TimerPWM(byte pin, unsigned long period, unsigned int duty)
{ init(pin, period, duty); }

void TimerPWM::init(byte pin, unsigned long period, unsigned int duty)
{
  setPin(pin);
  setPeriod(period); // microseconds
  setDuty(duty); // 1064
  
  Timer3.initialize(_period);
}

void TimerPWM::setPeriod(unsigned long period)
{ _period = period; }

void TimerPWM::setDuty(unsigned int duty)
{ _duty = duty; }

void TimerPWM::start()
{ Timer3.pwm(_pin, _duty); }

void TimerPWM::stop()
{ Timer3.disablePwm(_pin); }

// =============================================
// PinEventInterrupt
// =============================================
PinEventInterrupt::PinEventInterrupt()
{}

PinEventInterrupt::PinEventInterrupt(byte pin, unsigned long period, void* isr )
{
  setPin(pin);
  setISR(isr);
}

PinEventInterrupt::PinEventInterrupt(byte pin, bool activeState, unsigned long period, unsigned long duty)
{ init(pin, activeState, period, duty); }

void PinEventInterrupt::init(byte pin, bool activeState, unsigned long period, unsigned long duty)
{
  setPin(pin, !activeState);
  setGlobals(pin, period, duty);
  Timer3.initialize(PE_TIMER_RESOLUTION);
  setISR(pwmISR);
  Timer3.stop();  
}

void PinEventInterrupt::setGlobals(byte pin, unsigned long period, unsigned long duty)
{ 
  PE_PIN = pin;
  PE_PERIOD = period; 
  PE_DUTY_START = period - duty;
  PE_COUNTER = 0;
}

void PinEventInterrupt::setISR( void* isr)
{ Timer3.attachInterrupt( isr ); }

void PinEventInterrupt::pwmISR()
{  
  PE_COUNTER += PE_TIMER_RESOLUTION;

  // Begin duty 
  if(PE_COUNTER == PE_DUTY_START )
  {    
    digitalWrite(PE_PIN, HIGH);
    return;
  }

  // End period
  if( PE_COUNTER == PE_PERIOD )
  {
    digitalWrite(PE_PIN, LOW);
    PE_COUNTER = 0;
    return;
  }  
}

void PinEventInterrupt::start()
{ 
  digitalWrite(_pin, !activeState);
  Timer3.start(); 
}

void PinEventInterrupt::stop()
{ 
  Timer3.stop();
  Timer3.detachInterrupt();
  digitalWrite(_pin, !activeState); 
}
