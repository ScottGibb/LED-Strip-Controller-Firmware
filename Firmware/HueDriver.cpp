#include "HueDriver.h"
//Project Includes
#include "ColourDriver.h"
//System Includes
#include "stdint.h"

HueDriver::HueDriver(RGBColourDriver* colDriver){
  this->colDriver =colDriver;
  currentHSB.brightness =0;
  currentHSB.hue =0;
  currentHSB.saturation =0;

}

HueDriver::~HueDriver(){

}

void HueDriver:: setHue(HSB_t hsb){
  //https://www.rapidtables.com/convert/color/hsv-to-rgb.html
  float C = hsb.brightness*hsb.saturation;


}
HSB_t HueDriver:: getHue(void){
  return currentHSB;
}
