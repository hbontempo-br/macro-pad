/*
*/

#include <LayerManeger.h>

#include <Arduino.h>
#include <SimpleLED.h>

LayerManager::LayerManager(uint8_t buttonPin, uint8_t ledPins[2], int maxLayers)
{
  Button _button(buttonPin);
  SimpleLED _led1(ledPins[0]);
  SimpleLED _led2(ledPins[1]);
  _maxLayers = maxLayers;
  _layer = 1;
}

void LayerManager::begin()
{
  _button->begin();
  _led1->begin();
  _led2->begin();
  updateLigths();
}


int LayerManager::getCurrentLayer()
{
  updateLayer();
  updateLigths();
  return _layer;
}

void LayerManager::updateLayer()
{
  if (_button->pressed()) {
    Serial.println("LayerChanged");
    delay(1000);
    _layer = _layer + 1 % _maxLayers;
  }
}

void LayerManager::updateLigths()
{
  _led1->off();
  _led2->off();
  if ((_layer == 1) || (_layer ==2)){
    _led1->on();
  }
  if ((_layer == 2) || (_layer ==3)){
    _led1->on();
  }
}