#ifndef __LED_DRIVER_H__
#define __LED_DRIVER_H__


// Library Includes
#include <stdint.h>
#include <Arduino.h>

enum LED_COLOUR{
  RED_ =0,
  GREEN_ =1,
  BLUE_ = 2
};

const uint8_t MAX_PWM =255;
const uint8_t MIN_PWM =0;


const uint8_t NUM_LEDS =3;
const uint8_t LED_COLOUR_ENUM_LEN =NUM_LEDS;


class LEDDriver{
  public:
    LEDDriver(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
    ~LEDDriver();
    void setPWM(enum LED_COLOUR colour, uint8_t pwm);
    void setPWMS(uint8_t* pwms);
    uint8_t getPWM(enum LED_COLOUR colour);

  private:
  uint8_t pwm[3] = {0};
  uint8_t ledPins[LED_COLOUR_ENUM_LEN] ={0};

};




#endif