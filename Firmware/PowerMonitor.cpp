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

//Library Includes
#include <stdint.h>
#include <Arduino.h>
//Project Includes
#include "PowerSensors.h"


PowerMonitor::PowerMonitor(uint32_t currentPin, uint32_t voltagePin, uint32_t updatePeriod){
    powerStats.current =0;
    powerStats.voltage =0;
    powerStats.power =0;
    powerStats.lastUpdated =0;
    lastUpdateTime = 0;
    this->updatePeriod = updatePeriod;
    this->currentPin = currentPin;
    this->voltagePin = voltagePin;
    
}

PowerMonitor::~PowerMonitor(){

}

void PowerMonitor::loop(void){
    if(millis() - lastUpdateTime > updatePeriod){

        //Scan ADC Channels
        uint16_t voltSense = analogRead(voltagePin);
        uint16_t currentSense = analogRead(currentPin);

        //Perform Scalars and update

        powerStats.lastUpdated = millis();
        lastUpdateTime = millis();
    }
}

float PowerMonitor:: getCurrent(void){
    return powerStats.current;
}

float PowerMonitor:: getVoltage(void){
    return powerStats.voltage;
}

float PowerMonitor:: getPower(void){
    return powerStats.power;
}

Power_t PowerMonitor::getStats(void){
    return powerStats;
}

