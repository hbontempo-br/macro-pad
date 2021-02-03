/*
*/

#include <LayerManeger.h>

#include <Arduino.h>

LayerManager::LayerManager(uint8_t buttonPin, uint8_t ledPins[2], int maxLayers)
:  _button(Button(buttonPin))
,  _led1(SimpleLED(ledPins[0]))
,  _led2(SimpleLED(ledPins[1]))
,  _maxLayers(maxLayers)
,  _layer(0)
{
}

void LayerManager::begin()
{
  Serial.println((String)"Initializing LayerManager");
  _button.begin();
  _led1.begin();
  _led2.begin();
  updateLigths();
}


int LayerManager::getCurrentLayer()
{
  updateLayer();
  return _layer;
}

void LayerManager::updateLayer()
{
  _button.read();
  if (_button.wasPressed()) {
    _layer = (_layer + 1) % _maxLayers;
    Serial.println((String)"Layer selected: " + _layer);
    updateLigths();
  }
}

void LayerManager::updateLigths()
{
  _led1.off();
  _led2.off();
  if ((_layer == 0) || (_layer == 2)){
    _led1.on();
  }
  if ((_layer == 1) || (_layer == 2)){
    _led2.on();
  }
}