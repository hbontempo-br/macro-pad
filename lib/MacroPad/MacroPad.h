/*
  
*/

#ifndef MacroPad_h
#define MacroPad_h

#include <ArduinoSTL.h>
#include <limits.h>

#include <Keypad.h>

const int NO_KEY_PRESSED = -1;

class MacroPad
{
    public:
        MacroPad(std::vector<uint8_t> &rows, std::vector<uint8_t> &collumns);
        void begin();
        int* getKey();
    private:
        int _rows_size;
        int _collumns_size;
        Keypad _keypad;
        static uint8_t* vectorToArr(std::vector<uint8_t> &vector);
};



#endif