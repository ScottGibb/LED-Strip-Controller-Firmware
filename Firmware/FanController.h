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
#ifndef __FAN_CONTROLLER_H__
#define __FAN_CONTROLLER_H__

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
    FanController(uint32_t fanPin);
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
    uint8_t duty;
    uint8_t pwm;
    uint32_t fanPin;
};

#endif