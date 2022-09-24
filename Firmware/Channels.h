#ifndef __CHANNELS_H__
#define __CHANNELS_H__

#include <Arduino.h>

enum CHANNEL{
  CHANNEL_NS = 0,
  CHANNEL_1 = 1,
  CHANNEL_2 = 2,
  CHANNEL_3 = 3

};

#define CHANNEL_1_G_PIN PB1
#define CHANNEL_1_R_PIN PB0
#define CHANNEL_1_B_PIN PA7

#define CHANNEL_2_G_PIN PA3
#define CHANNEL_2_R_PIN PA2
#define CHANNEL_2_B_PIN PA1

#define CHANNEL_3_G_PIN PB6
#define CHANNEL_3_R_PIN PB7
#define CHANNEL_3_B_PIN PB8

#define STATUS_LED_PIN PC13
#endif