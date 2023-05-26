/**
 * @file PowerMonitor.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief  This class is responsible for scanning the appropriate channel and then calculates the power
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "PowerMonitor.h"
// Project Includes
#include "PowerSensors.h"
// System Includes
#include <Arduino.h>
#include <stdint.h>

PowerMonitor::PowerMonitor(uint32_t currentPin, uint32_t voltagePin, uint32_t updatePeriod) : VOLTAGE_PIN(voltagePin), CURRENT_PIN(currentPin), UPDATE_PERIOD(updatePeriod)
{
    powerStats.current = 0;
    powerStats.voltage = 0;
    powerStats.power = 0;
    powerStats.lastUpdated = 0;
    lastUpdateTime = 0;
}

PowerMonitor::~PowerMonitor()
{
}

void PowerMonitor::loop()
{
    if (millis() - lastUpdateTime > UPDATE_PERIOD)
    {

        // Scan ADC Channels
        uint16_t voltSense = analogRead(VOLTAGE_PIN);
        uint16_t currentSense = analogRead(CURRENT_PIN);
        // Perform Scalars and update
        float voltVoltage = static_cast<float>((1.0 * voltSense / ADC_RANGE) * MAX_ADC_VOLTAGE);
        float voltCurrent = static_cast<float>((1.0 * currentSense / ADC_RANGE) * MAX_ADC_VOLTAGE);

        powerStats.voltage = VOLTAGE_SCALAR * voltVoltage;
        powerStats.current = CURRENT_SENSOR_SCALAR * voltCurrent;

        powerStats.power = powerStats.current * powerStats.voltage;

        powerStats.lastUpdated = millis();
        lastUpdateTime = millis();
    }
}

float PowerMonitor::getCurrent()
{
    return powerStats.current;
}

float PowerMonitor::getVoltage()
{
    return powerStats.voltage;
}

float PowerMonitor::getPower()
{
    return powerStats.power;
}

Power_t PowerMonitor::getStats()
{
    return powerStats;
}
