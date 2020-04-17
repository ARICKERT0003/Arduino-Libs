#include "PinEvent.h"

extern unsigned long Timer3_ISR_PERIOD = 1000000; // 1s -> us
int SERVO_POS = 0;
int SERVO_POS_START = 0;
int SERVO_POS_END = 0;
unsigned long SERVO_PERIOD = 0;
unsigned long SERVO_PERIOD_COUNTER = 0;
unsigned long SERVO_DUTY_START = 0;
Servo* PTR_SERVO;

TimedServo::TimedServo()
{}

void TimedServo::init(byte pin, int pos)
{
  attachServo(pin);
  PTR_SERVO->write(pos); 
  SERVO_POS = pos;      
}

void TimedServo::attachServo(byte pin)
{
  PTR_SERVO = new Servo;
  PTR_SERVO->attach(pin);
}

void TimedServo::setSweep(unsigned long period, unsigned long duty, int startPOS, int endPOS)
{
  SERVO_PERIOD = period;
  SERVO_DUTY_START = period - duty;
  SERVO_POS_START = startPOS;
  SERVO_POS_END = endPOS;
  
  Timer3.initialize(Timer3_ISR_PERIOD);
  setISR(TimedServo::timedSweep);
  Timer3.stop();         
}

void TimedServo::setISR( void* isr)
{ Timer3.attachInterrupt( isr ); }

void TimedServo::start(int pos)
{ 
  Serial.println("timedServo::start");
  PTR_SERVO->write(pos);
  SERVO_POS = pos;
  Timer3.start(); 
}

void TimedServo::stop(int pos)
{ 
  Timer3.stop();
  Timer3.detachInterrupt();
  PTR_SERVO->write(pos);
  SERVO_POS = pos;
}

void TimedServo::timedSweep()
{
  SERVO_PERIOD_COUNTER += Timer3_ISR_PERIOD;

  if(SERVO_PERIOD_COUNTER < SERVO_DUTY_START)
  { return; }

  if(SERVO_PERIOD_COUNTER == SERVO_PERIOD)
  {
    SERVO_PERIOD_COUNTER = 0;
    return;
  }
  
  if(SERVO_POS == SERVO_POS_START)
  {
    PTR_SERVO->write(SERVO_POS_END);
    SERVO_POS = SERVO_POS_END;    
  }
  else
  {
    PTR_SERVO->write(SERVO_POS_START);
    SERVO_POS = SERVO_POS_START;
  }      
}
