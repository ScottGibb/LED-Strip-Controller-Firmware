/**
 * @file PowerMonitor.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Power Monitor class header file
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef POWER_MONITOR_H
#define POWER_MONITOR_H

#include "stdint.h"

/**
 * @brief Power statistics struct
 *
 */
typedef struct
{
    float power;
    float current;
    float voltage;
    uint32_t lastUpdated;
} Power_t;

class PowerMonitor
{
    /**
     * @brief Handles all computation regarding current and voltage and computes its power. The loop() function must be called in the main loop
     */
public:
    /**
     * @brief Construct a new Power Monitor object
     *
     * @param currentPin The pin that the current sensor is connected too
     * @param voltagePin The pin that the voltage sensor is connected too
     * @param updatePeriod The time in which the sensors are polled
     */
    PowerMonitor(const uint32_t currentPin, const uint32_t voltagePin, const uint32_t updatePeriod);
    /**
     * @brief Destroy the Power Monitor object
     *
     */
    ~PowerMonitor();
    /**
     * @brief Calculates the new power stats
     *
     */
    void loop(void);
    /**
     * @brief Get the last known current value, measured in Amps
     *
     * @return float
     */
    float getCurrent(void);
    /**
     * @brief Get the last known voltage measured
     *
     * @return float
     */
    float getVoltage(void);
    /**
     * @brief Get the last known power calculated
     *
     * @return float
     */
    float getPower(void);
    /**
     * @brief Gets the current power stats
     *
     * @return Power_t
     */
    Power_t getStats(void);

private:
    const uint32_t VOLTAGE_PIN;
    const uint32_t CURRENT_PIN;
    const uint32_t UPDATE_PERIOD;
    uint32_t lastUpdateTime;

    Power_t powerStats;
};

#endif