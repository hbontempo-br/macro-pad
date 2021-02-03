/*
*/

#include <SimpleLED.h>

SimpleLED::SimpleLED(int ledPin)
: _ledPin(ledPin)
{
}

void SimpleLED::begin()
{
    Serial.println((String)"Initializing SimpleLED (pin " + _ledPin + ")");
    pinMode(_ledPin, OUTPUT);
}

void SimpleLED::on()
{
    Serial.println((String)"SimpleLED on (pin " + _ledPin + ")");
    digitalWrite(_ledPin, HIGH);
}

void SimpleLED::off()
{
    Serial.println((String)"SimpleLED of (pin " + _ledPin + ")");
    digitalWrite(_ledPin, LOW);
}