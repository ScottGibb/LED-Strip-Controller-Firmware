/**
 * @file FanController.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Header File associated with the Fan Controller class. Which controls a Fan using PWM
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include <stdint.h>

class FanController
/**
 * @brief FanController class responsible for controlling a fan using PWM
 *
 */
{
public:
    /**
     * @brief Construct a new Fan Controller object
     *
     * @param fanPin
     */
    FanController(const uint32_t fanPin);
    /**
     * @brief Destroy the Fan Controller object
     *
     */
    ~FanController();
    /**
     * @brief Changes the fan duty cycle (0-100)
     *
     * @param duty
     */
    void changeDuty(uint8_t duty);
    /**
     * @brief Get the currentDuty
     *
     * @return uint8_t
     */
    uint8_t getDuty(void);

private:
    const uint8_t MAX_PWM = 255;
    const uint32_t FAN_PIN;
    uint8_t duty;
    uint8_t pwm;
};

#endif//FAN_CONTROLLER_H