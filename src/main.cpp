#include <Arduino.h>

#include <Button.h>
#include <Keyboard.h>
#include <Keypad.h>
#include <Rotary.h>

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

// KeyPad config
uint8_t const ROWS = 2;
uint8_t const COLS = 4;
uint8_t rowPins[ROWS] = {4, 5};
uint8_t colPins[COLS] = {6, 7, 8, 9};
char keys[] = "ABCDEFGH";
Keypad keypad = Keypad(keys, rowPins, colPins, ROWS, COLS);

uint8_t buttonActions[] = {
  KEY_F13, KEY_F14, KEY_F15, KEY_F16,
  KEY_F17, KEY_F18, KEY_F19, KEY_F20
};

// Encoders
Rotary leftEncoder = Rotary(MOSI, A10);
Rotary rigthEncoder = Rotary(SCK, MISO);


// Layers
Button layerButton(A0);
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

  Keyboard.begin();

  leftEncoder.begin();
  rigthEncoder.begin();

  layerButton.begin();
  currentLayer = 0; // TODO: ave value between restarts
  setupLayers();
}

void loop() {
  if (layerButton.pressed()) {
    currentLayer = (currentLayer + 1) % 3;
    Serial.println((String)"Layer selected: " + currentLayer);
    // Still not handling LEDs
  }
  uint8_t layerAlterer[2] = {layerAlterers[currentLayer][0], layerAlterers[currentLayer][1]};
  
  unsigned char leftRotation = leftEncoder.process();
  if (leftRotation != DIR_NONE) {
    uint8_t action = leftRotation == DIR_CW ? KEY_F21 : KEY_F22;
    executeAction(layerAlterer, action);
  }

  unsigned char rigthRotation = leftEncoder.process();
  if (rigthRotation != DIR_NONE) {
    uint8_t action = rigthRotation == DIR_CW ? KEY_F21 : KEY_F22;
    executeAction(layerAlterer, action);
  }


  auto key = keypad.getKey();
  if (key)
  {
    auto index = key - 'A';
    uint8_t buttonAction = buttonActions[index];

    executeAction(layerAlterer, buttonAction);
  }


  delay(1);
}

