/**
 * @file STM32F103C8T6Channels.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Channel Definitions Header File
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CHANNELS_H
#define CHANNELS_H

// Library Includes
#include <Arduino.h>
#include <stdint.h>
/**
 * @brief Channel Selection Enum
 *
 */
enum CHANNEL
{
  CHANNEL_NS = 0,
  CHANNEL_1 = 1,
  CHANNEL_2 = 2,
  CHANNEL_3 = 3

};
#define NUM_CHANNELS (uint8_t)3

/**
 * @brief Veroboard Pin Selections
 *
 */
// RGB Channel One Pins
#define CHANNEL_1_G_PIN PB1
#define CHANNEL_1_R_PIN PB0
#define CHANNEL_1_B_PIN PA7

// RGB Channel Two Pins
#define CHANNEL_2_G_PIN PA3
#define CHANNEL_2_R_PIN PA2
#define CHANNEL_2_B_PIN PA1

// RGB Channel Three Pins
#define CHANNEL_3_G_PIN PB6
#define CHANNEL_3_R_PIN PB7
#define CHANNEL_3_B_PIN PB8

// Status LED Pin
#define STATUS_LED_PIN PC13
#endif // CHANNELS_H