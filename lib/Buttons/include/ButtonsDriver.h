/**
 * @file ButtonsDriver.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef BUTTONS_DRIVER_H
#define BUTTONS_DRIVER_H

// Library Includes
#include <stdint.h>

// Function Pointer
typedef void (*func_type)(void);

/**
 * @brief Buttons Driver Class
 * Class Declaration of Buttons Driver
 */
class ButtonsDriver
{
public:
  /**
   * @brief Construct a new Buttons Driver:: Buttons Driver object
   * Buttons Driver Constructor. Each Array should be ordered such that when buttonPins[i] is pressed funcs[i] is called
   * @param[in] buttonPins A Pointer to the pins used for the buttons
   * @param[in] numButtons The Number of Buttons
   * @param[in] funcs The function assigned to each button
   */
  ButtonsDriver(const uint32_t *buttonPins, const uint8_t numButtons, const func_type *funcs);
  /**
   * @brief ButtonsDriver Deconstructor
   *
   * @return ButtonsDriver::
   */
  ~ButtonsDriver();
  /**
   * @brief ButtonsDriver Main Loop
   * To be called once every iteration of the main loop of the firmware.
   */
  void loop(void);

  ButtonsDriver(const ButtonsDriver &) = delete;
  ButtonsDriver &operator=(const ButtonsDriver &) = delete;

private:
  const uint32_t *buttonPins;
  const uint8_t numButtons;
  const func_type *functions;
  int *buttonStates;
  int *lastButtonStates;
  uint32_t *lastDebounceTimes;
  const uint32_t MAX_DEBOUNCE_TIME = 50;
};

#endif // BUTTONS_DRIVER_H