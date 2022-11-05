/**
 * @file FadeDriver.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Header file associated with the Fade Driver, an abstraction layer above ColourDriver, providing fading effects logic of the LEDs using a soft timer implementation.
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __FADE_DRIVER__H_
#define __FADE_DRIVER__H_

//Library Includes
#include <stdint.h>

//Project Includes
#include "ColourDriver.h"

//Constants
const uint32_t NUM_MODES = 6;

/**
 * @brief Enum describing the different fade effects that the Fade Driver can do.
 * 
 */
enum FADE_TYPE {
  NONE = 0,          /**< No Fade Effect*/
  SINE = 1,          /**< Sinusoidal Effect*/
  SQUARE = 2,        /**< Pulsing Effect*/
  TRIANGLE = 3,      /**< Triangular Effect*/
  SAWTOOTH = 4,      /**< Sinusoidal Effect*/
  COLOUR_CHANGE = 5, /**< Colour Changing Effect*/
};

/**
 * @brief Struct for using the FadeDriver object, outlining key paramaters to run the fading software timer based logic
 */
typedef struct {
  enum FADE_TYPE fade = SINE; /**< Type of Fade to be applied*/
  uint32_t period = 0;        /**< Period of the fade wave*/
  uint32_t halfPeriod = 0;    /**< Half ot the period*/
  uint8_t maxBrightness = 0;  /**< Maximum brightness of the fade cycle*/
} FadeState_t;


/**
 * @brief FadeDriver object used to provide interesting fade patterns via a software timed solution. Instantiate the object, call the startFade() function and repeatably call FadeLoop().
 * 
 */
class FadeDriver {

public:
  FadeDriver(RGBColourDriver *driver);
  void startFade(enum FADE_TYPE fade, uint32_t period, uint8_t maxBrightness);
  void startFade(FadeState_t fadeState);
  FadeState_t getFade(void);
  void fadeLoop(void);
  void stopFade(void);

private:
  RGBColourDriver *driver;
  FadeState_t currentState;
  uint32_t lastFadeUpdateTime;
  uint32_t currentStep;
  void squareWave(void);
  void sawToothWave(void);
  void triangleWave(void);
  void sineWave(void);
  bool getOverride(void);
  void setOverride(bool override);
};



#endif