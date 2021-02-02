/*
  
*/

#ifndef SimpleLED_h
#define SimpleLED_h

#include <Arduino.h>

class SimpleLED
{
    public:
        SimpleLED(int ledPin);
        void on();
        void off();
    private:
        int _ledPin;
};



#endif