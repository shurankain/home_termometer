#include <Arduino.h>

const int motionPin = 8;

void setup()
{
  pinMode(motionPin, INPUT);
}

void loop()
{
  if (digitalRead(motionPin) == HIGH)
  {
    // show data
  }
  else
  {
    // goto sleep
  }
}