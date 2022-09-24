#include "ColourDriver.h"

ColourDriver::ColourDriver(LEDDriver *driver) {
  this->driver = driver;
  uint8_t zeroPWM[NUM_LEDS] = { 0 };
  this->driver->setPWMS(zeroPWM);
  colourState.bluePWM = 0;
  colourState.redPWM = 0;
  colourState.greenPWM = 0;
  colourState.brightness = 0;
}
ColourDriver::~ColourDriver() {
}

void ColourDriver::setColour(enum Colour colour) {
  setColour(colour, colourState.brightness);
}
void ColourDriver::setColour(enum Colour colour, float brightness) {
  uint8_t colourPWMS[NUM_LEDS] = { 0 };
  switch (colour) {

    case RED:
      colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
      break;
    case GREEN:
      colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
      break;
    case BLUE:
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case WHITE:
      colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case ROSE:
      colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[2] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Blue LED
      break;
    case MAGENTA:
      colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case VIOLET:
      colourPWMS[0] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Red LED
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case AZURE:
      colourPWMS[1] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Green LED
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case CYAN:
      colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case AQUAMARINE:
      colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[2] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Blue LED
      break;
    case CHARTREUSE:
      colourPWMS[0] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Green LED
      colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
      break;
    case YELLOW:
      colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
      break;
    case ORANGE:
      colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[1] = (brightness / 200.0) * MAX_PWM;
      break;
  }
  colourState.colour = colour;
  setPWMSignals(colourPWMS, brightness);
}
enum Colour ColourDriver::getColour() {
  return colourState.colour;
}


void ColourDriver::setPWMSignals(uint8_t *colourPWMS, float brightness) {
  colourState.redPWM = colourPWMS[0];
  colourState.greenPWM = colourPWMS[1];
  colourState.bluePWM = colourPWMS[2];
  colourState.brightness = brightness;
  driver->setPWMS(colourPWMS);
}



void ColourDriver::setBrightness(uint8_t brightness) {
  setColour(colourState.colour, brightness);
}
uint8_t ColourDriver::getBrightness() {
}