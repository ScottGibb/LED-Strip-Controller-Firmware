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
#ifndef FADE_DRIVER_H
#define FADE_DRIVER_H

// Project Includes
#include "ColourDriver.h"
// Library Includes
#include <stdint.h>

// Constants
const uint32_t NUM_MODES = 8;

/**
 * @brief Enum describing the different fade effects that the Fade Driver can do.
 *
 */
enum FADE_TYPE
{
  NONE = 0,          /**< No Fade Effect*/
  SINE = 1,          /**< Sinusoidal Effect*/
  SQUARE = 2,        /**< Pulsing Effect*/
  TRIANGLE = 3,      /**< Triangular Effect*/
  SAWTOOTH = 4,      /**< Sinusoidal Effect*/
  COLOUR_CHANGE = 5, /**< Colour Changing Effect*/
  RGB_CONTROL = 6,   /** RGB Control **/
  HUE_CONTROL = 7    /** HUE Control **/
};

/**
 * @brief Struct for using the FadeDriver object, outlining key paramaters to run the fading software timer based logic
 */
typedef struct
{
  enum FADE_TYPE fade = SINE; /**< Type of Fade to be applied*/
  uint32_t period = 0;        /**< Period of the fade wave*/
  uint32_t halfPeriod = 0;    /**< Half ot the period*/
  uint8_t maxBrightness = 0;  /**< Maximum brightness of the fade cycle*/
} FadeState_t;

/**
 * @brief FadeDriver object used to provide interesting fade patterns via a software timed solution. Instantiate the object, call the startFade() function and repeatably call FadeLoop().
 *
 */
class FadeDriver
{

public:
  /**
   * @brief Construct a new Fade Driver:: Fade Driver object
   * @param[in] driver The colour Driver object used for the specific led channel
   */
  FadeDriver(RGBColourDriver *driver);
  /**
   * @brief FadeDrivers deconstructor
   *
   */
  ~FadeDriver();
  /**
   * @brief Starts the next fade cycle with the chosen paramaters
   *
   * @param[in] fade the type of fade to be applied
   * @param[in] period the period of the fade signal
   * @param[in] maxBrightness the maximum brightness to be achieved during the cycle
   */
  void startFade(enum FADE_TYPE fade, uint32_t period, uint8_t maxBrightness);
  /**
   * @brief Changes the current fade and all of its settings to the new fade provided
   *
   * @param[in] fadeState the fade to be changed to
   */
  void startFade(FadeState_t fadeState);
  /**
   * @brief Gets the current fade state
   * @return FadeState the current fade and its settings
   */
  FadeState_t getFade();
  /**
   * @brief The Fad Driver application loop
   * Call at frequency faster than 1/STEP_SIZE in order to maintain smooth fade transitions
   */
  void fadeLoop();
  /**
   * @brief Stops the current fade and resets all fade settings to default
   *
   */
  void stopFade();

private:
  const uint32_t STEP_SIZE = 1; // ms
  RGBColourDriver *driver;
  FadeState_t currentState;
  uint32_t lastFadeUpdateTime;
  uint32_t currentStep;
  /**
   * @brief Soft timer implementation of the square wave signal
   *
   */
  void squareWave();
  /**
   * @brief Soft timer implementation of the sawTooth Waveform
   *
   */
  void sawToothWave();
  /**
   * @brief Soft timer implementation of the triangular waveform
   *
   */
  void triangleWave();
  /**
   * @brief Soft Timer implementation of the sine waveform
   *
   */
  void sineWave();
};

#endif // FADE_DRIVER_H