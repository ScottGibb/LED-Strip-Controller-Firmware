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
    PowerMonitor(uint32_t currentPin, uint32_t voltagePin, uint32_t updatePeriod);
    /**
     * @brief Destroy the Power Monitor object
     * 
     */
    ~PowerMonitor();
    /**
     * @brief Calculates the new power stats
     * 
     */
    void loop();
    /**
     * @brief Get the last known current value, measured in Amps
     * 
     * @return float 
     */
    float getCurrent();
    /**
     * @brief Get the last known voltage measured 
     * 
     * @return float 
     */
    float getVoltage();
    /**
     * @brief Get the last known power calculated
     * 
     * @return float 
     */
    float getPower();
    /**
     * @brief Gets the current power stats
     * 
     * @return Power_t 
     */
    Power_t getStats();

private:
    uint32_t updatePeriod;
    uint32_t lastUpdateTime;
    Power_t powerStats;
    uint32_t voltagePin;
    uint32_t currentPin;
};