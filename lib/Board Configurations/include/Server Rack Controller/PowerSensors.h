/**
 * @file PowerSensors.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief This file contains all the pins and scalars associated with the power sensors hardware
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef POWER_SENSORS_H
#define POWER_SENSORS_H

#define ADC_RANGE (1 << 12)
#define MAX_ADC_VOLTAGE 3.3F

#define VOLTAGE_DIVIDER_R1 100.0F // Measured Resistor
#define VOLTAGE_DIVIDER_R2 100.0F
float const VOLTAGE_SCALAR = ((VOLTAGE_DIVIDER_R1) / (VOLTAGE_DIVIDER_R1 + VOLTAGE_DIVIDER_R2));
#define VOLTAGE_SENSOR_PIN 10 // todo Change to actual pin

#define CURRENT_SENSOR_RS 10000.0F
#define CURRENT_SENSOR_RL 10000.0F
float const CURRENT_SENSOR_SCALAR = (1000.0F / (CURRENT_SENSOR_RS * CURRENT_SENSOR_RL));
#define CURRENT_SENSOR_PIN 10 // todo Change to actual pin

#define POWER_SENSOR_UPDATE_PERIOD 200 // ms
#endif                                 // POWER_SENSORS_H
