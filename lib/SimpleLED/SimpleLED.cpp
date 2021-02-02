/*
*/

#include <SimpleLED.h>

SimpleLED::SimpleLED(int ledPin)
{
    _ledPin = ledPin;
    pinMode(_ledPin, OUTPUT);
}

void SimpleLED::on()
{
    digitalWrite(_ledPin, HIGH);
}

void SimpleLED::off()
{
    digitalWrite(_ledPin, LOW);
}