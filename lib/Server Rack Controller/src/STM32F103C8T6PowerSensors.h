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
#ifndef __POWER_SENSORS_H__
#define __POWER_SENSORS_H__

#define VOLTAGE_DIVIDER_R1 100.0f // Measured Resistor
#define VOLTAGE_DIVIDER_R2 100.0f
float const VOLTAGE_SCALAR = ((VOLTAGE_DIVIDER_R1) / (VOLTAGE_DIVIDER_R1 + VOLTAGE_DIVIDER_R2));
#define VOLTAGE_SENSOR_PIN 10 // todo Change to actual pin

#define CURRENT_SENSOR_RS 10000.0f
#define CURRENT_SENSOR_RL 10000.0f
float const CURRENT_SENSOR_SCALAR = (1000.0f / (CURRENT_SENSOR_RS * CURRENT_SENSOR_RL));
#define CURRENT_SENSOR_PIN 10 // todo Change to actual pin

#define POWER_SENSOR_UPDATE_PERIOD 200 // ms
#endif
