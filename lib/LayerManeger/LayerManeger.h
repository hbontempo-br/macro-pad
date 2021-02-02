/*
  
*/

#ifndef LayerManager_h
#define LayerManager_h

#include <Arduino.h>
#include <Button.h>
#include <SimpleLED.h>

class LayerGetter
{
    public:
        virtual int getCurrentLayer(); 
};



class LayerManager: LayerGetter
{
    public:
        LayerManager(uint8_t buttonPin, uint8_t ledPins[2], int maxLayers);
        int getCurrentLayer() override;
    private:
        void updateLayer();
        void updateLigths();
        int _layer;
        int _maxLayers;
        SimpleLED* _led1;
        SimpleLED* _led2;
        Button* _button;
};


#endif