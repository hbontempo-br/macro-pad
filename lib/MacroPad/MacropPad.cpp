/*
*/

#include <MacroPad.h>

char KEYS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

MacroPad::MacroPad(std::vector<uint8_t> &rows, std::vector<uint8_t> &collumns)
:   _rows_size(rows.size())
,   _collumns_size(collumns.size())
,   _keypad(Keypad(KEYS, vectorToArr(rows), vectorToArr(collumns), _rows_size, _collumns_size))
{
}

uint8_t* MacroPad::vectorToArr(std::vector<uint8_t> &vector)
{
    uint size = vector.size();
    static uint8_t arr[20];
    for (uint r = 0; r < size ; r++){
        arr[r] = vector[r];
    };
    return arr;
}

int* MacroPad::getKey()
{  
    static int keyPressed[] = {};
    keyPressed[0] = NO_KEY_PRESSED;
    keyPressed[1] = NO_KEY_PRESSED;
    
    // Serial.println((String)"NO_KEY_PRESSED " + NO_KEY_PRESSED);
    // Serial.println((String)"Key: " + keyPressed[0] + "/" + keyPressed[1]);



    char key = _keypad.getKey();
    // char key = 'C';
    if (key)
    {
        int index = key - 'A';
        Serial.println((String)"Key " + key);
        Serial.println((String)"Index " + index);
        Serial.println((String)"RowSize " + _rows_size);
        Serial.println((String)"ColSize " + _collumns_size);
        
        keyPressed[0] = index / _collumns_size; // row pressed
        keyPressed[1] = index % _collumns_size; // collumn pressed
        Serial.println((String)"Key: " + keyPressed[0] + "/" + keyPressed[1]);
    }
    return keyPressed;
}