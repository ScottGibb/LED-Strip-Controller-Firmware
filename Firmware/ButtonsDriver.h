#ifndef __BUTTONS_DRIVER_H__
#define __BUTTONS_DRIVER_H__

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
  ButtonsDriver(uint32_t *buttonPins, uint8_t numButtons, func_type *funcs);
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

private:
  uint32_t *buttonPins;
  uint8_t numButtons;
  uint32_t *lastDebounceTimes;
  int *buttonStates;
  int *lastButtonStates;
  const uint32_t MAX_DEBOUNCE_TIME = 50;
  func_type *functions;
};

#endif