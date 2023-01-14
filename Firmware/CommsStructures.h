#ifndef __COMMSSTRUCTURES_H__
#define __COMMSSTRUCTURES_H__

#include <stdint.h>

// Project Includes
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "Channels.h"
#include "Main.h"

// External Constants
constexpr uint8_t controlCommsPacketLength = 14; //HUE Control +1
constexpr uint8_t channelPacketSize = 4;                                             // CHANNEL ID + 3 * pwm values
constexpr uint8_t telemetryCommsPacketLength = channelPacketSize * NUM_CHANNELS + 2; // TX_MSG_ID + number of channels

/**
 * @brief Commmunication Protocol Struct used to outline the Comms Packet being sent to the MCU for control of the system.
 *
 */
typedef struct
{
  enum CHANNEL channel : 8; // 8 Bits Byte 0
  enum FADE_TYPE mode : 8;  // 16 Bits Byte 1
  enum COLOUR colour : 8;   // 32 Bits Byte 2-3
  uint8_t brightness;       // 40 Bits Byte 4
  uint32_t period;          // 72 Bits Byte 5-7
} FunctionsCommsProtocol_t;

typedef struct
{
  enum CHANNEL channel : 8; // 8 Bits Byte 0
  enum FADE_TYPE mode : 8;  // 16 Bits Byte 1
  uint8_t redPWM;           // 24 Bits Byte 2
  uint8_t greenPWM;         // 32 Bits Byte 3
  uint8_t bluePWM;          // 30 Bits Byte 4
} RGBControlCommsProtocol_t;

typedef struct
{
  enum CHANNEL channel : 8; // 8 Bits Byte 0
  enum FADE_TYPE mode : 8;  // 16 Bits Byte 1
  float hue;                // 24 Bits Byte 2-5
  float saturation;         // 32 Bits Byte 6-9
  float brightness;         // 30 Bits Byte 10-13
} HueControlCommsProtocol_t;

/**
 * @brief Comms Message Union used to represent the byte array as a struct
 *
 */
union RxCommsMessage_t
{ // This doesnt gaurantee alignmnet within program memory
  FunctionsCommsProtocol_t commsPacket;
  uint8_t commsBytes[controlCommsPacketLength];
};

/**
 * @brief TX Message IDs
 *
 */
enum TX_MSG_ID
{
  LED_UPDATE = 0,
  PWR_UPDATE = 1
};

#endif