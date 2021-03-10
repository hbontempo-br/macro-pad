#include <ArduinoSTL.h>

#include <Keyboard.h>
#include <Keypad.h>
#include <Rotary.h>

#include <LayerManeger.h>
#include <MacroPad.h>

std::vector<uint8_t> rows = {4, 5};
std::vector<uint8_t> collumns = {6, 7, 8, 9};
MacroPad macroPad(rows, collumns);



//
//  Key Matrix:
//    F13 | F14 | F15 | F16 
//    F17 | F18 | F19 | F20
//
//  Left-Encoder:
//    clockwise:        F21
//    anti-clockwise:   F22
//
//  Rigth-Encoder:
//    clockwise:        F23
//    anti-clockwise:   F24
//
//
//  Layers:
//    0: []
//    1: [Ctrl]
//    2: [Shift]
//

// // KeyPad config
// uint8_t const ROWS = 2;
// uint8_t const COLS = 4;
// uint8_t rowPins[ROWS] = {4, 5};
// uint8_t colPins[COLS] = {6, 7, 8, 9};
// char keys[] = "ABCDEFGH";
// Keypad keypad = Keypad(keys, rowPins, colPins, ROWS, COLS);

// uint8_t buttonActions[] = {
//   KEY_F13, KEY_F14, KEY_F15, KEY_F16,
//   KEY_F17, KEY_F18, KEY_F19, KEY_F20
// };

// Encoders
Rotary leftEncoder = Rotary(MOSI, A10);
Rotary rigthEncoder = Rotary(SCK, MISO);


// Layers
uint8_t inputLEDs[2] = {A2, A3};
LayerManager layerManager(A0, inputLEDs, 3);
uint8_t currentLayer;

uint8_t layerAlterers[3][2];
void setupLayers(){
  layerAlterers[0][0] = NO_KEY; layerAlterers[0][1] = NO_KEY;
  layerAlterers[1][0] = KEY_LEFT_CTRL; layerAlterers[1][1] = KEY_LEFT_CTRL;
  layerAlterers[2][0] = KEY_LEFT_SHIFT; layerAlterers[2][1] = KEY_LEFT_CTRL;
}


void executeAction(uint8_t layerAlterer[2], uint8_t action ) {
  Serial.println((String)"Executing action: " + char(layerAlterer[0]) + " / " + char(layerAlterer[1]) + " / " + char(action));
  for (int i = 0; i < 2; i++){
    if (layerAlterer[i] != NO_KEY){
      Keyboard.press(layerAlterer[i]);
    }
  }

  Keyboard.press(action);

  Keyboard.releaseAll();

}


void setup(){
  Serial.begin(9600);


  // Countdown for debugging
  for (int i = 10; i > 0; i--){
    Serial.println((String)"Starting in ..." + i);
    delay(1000);
  };

  layerManager.begin();
  Keyboard.begin();

  leftEncoder.begin();
  rigthEncoder.begin();

  setupLayers();
}

void loop() {
  int currentLayer = layerManager.getCurrentLayer();
  uint8_t layerAlterer[2] = {layerAlterers[currentLayer][0], layerAlterers[currentLayer][1]};

  unsigned char leftRotation = leftEncoder.process();
  if (leftRotation != DIR_NONE) {
    uint8_t action = leftRotation == DIR_CW ? KEY_F21 : KEY_F22;
    executeAction(layerAlterer, action);
  }

  unsigned char rigthRotation = rigthEncoder.process();
  if (rigthRotation != DIR_NONE) {
    uint8_t action = rigthRotation == DIR_CW ? KEY_F23 : KEY_F24;
    executeAction(layerAlterer, action);
  }


  int* key = macroPad.getKey();
  int row = key[0];
  int col = key[1];
  if(row != NO_KEY_PRESSED && col != NO_KEY_PRESSED)
  {
    Serial.println((String)"" + row + "/" + col);
    delay(3000);
  }

  // auto key_ = keypad.getKey();
  // if (key_)
  // {
  //   Serial.println((String)"Key" + key_);
  //   auto index = key_ - 'A';
  //   uint8_t buttonAction = buttonActions[index];

  //   executeAction(layerAlterer, buttonAction);
  // }


  delay(1);

};