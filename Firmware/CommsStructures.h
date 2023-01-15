#ifndef __COMMSSTRUCTURES_H__
#define __COMMSSTRUCTURES_H__

#include <stdint.h>

// Project Includes
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "Channels.h"
#include "Main.h"

// External Constants
constexpr uint8_t controlCommsPacketLength = 10; // Data Structures Padded to this size

// Teleemetry Data Sizes
constexpr uint8_t channelPacketSize = 4;                                             // CHANNEL ID + 3 * pwm values
constexpr uint8_t telemetryCommsPacketLength = channelPacketSize * NUM_CHANNELS + 2; // TELEMETRY_CMD_ID + number of channels

/**
 * @brief Telemetry Message IDs
 *
 */
enum TELEMETRY_CMD_ID
{
  LED_UPDATE = 0,
  PWR_UPDATE = 1
};

/**
 * @brief CTRL_CMDS IDs
 */
enum CTRL_CMD_ID
{
  LED_CHANGE = 0
};
/**
 * @brief Commmunication Protocol Struct used to outline the Comms Packet being sent to the MCU for control of the system.
 *
 */
typedef struct
{
  enum CTRL_CMD_ID : 8;     // 8 Bits Byte 0
  enum CHANNEL channel : 8; // 16 Bits Byte 1
  enum FADE_TYPE mode : 8;  // 32 Bits Byte 2
  enum COLOUR colour : 8;   // 40 Bits Byte 3-4
  uint8_t brightness;       // 48 Bits Byte 5
  uint32_t period;          // 80 Bits Byte 6-8
} FunctionsCommsProtocol_t;

typedef struct
{
  enum CTRL_CMD_ID : 8;     //  8 Bits Byte 0
  enum CHANNEL channel : 8; // 16 Bits Byte 1
  enum FADE_TYPE mode : 8;  // 24 Bits Byte 2
  uint8_t redPWM;           // 32 Bits Byte 3
  uint8_t greenPWM;         // 40 Bits Byte 4
  uint8_t bluePWM;          // 48 Bits Byte 5
} RGBControlCommsProtocol_t;

typedef struct
{
  enum CTRL_CMD_ID : 8;     // 8 Bits Byte 0
  enum CHANNEL channel : 8; // 8 Bits Byte 1
  enum FADE_TYPE mode : 8;  // 16 Bits Byte 2
  uint16_t hue;             // 24 Bits Byte 3-4
  uint8_t saturation;       // 32 Bits Byte 5
  uint8_t brightness;       // 30 Bits Byte 6
} HueControlCommsProtocol_t;


#endif