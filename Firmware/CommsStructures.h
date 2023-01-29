#ifndef __COMMSSTRUCTURES_H__
#define __COMMSSTRUCTURES_H__

// Library Includes
#include <stdint.h>

// Project Includes
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "Channels.h"
#include "Main.h"
#include "MemoryMap.h"

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
  LED_CHANGE = 0,
  USER_MODE_CHANGE = 1,
  USER_MODE_SAVE = 2,
  USER_MODE_LOAD = 3
};
/**
 * @brief FunctionsCommsProtocol_t outlining Fade Driver command Structure
 *
 */
typedef struct
{
  enum CTRL_CMD_ID command : 8; // 8 Bits Byte 0
  enum CHANNEL channel : 8;     // 16 Bits Byte 1
  enum FADE_TYPE mode : 8;      // 32 Bits Byte 2
  enum COLOUR colour : 8;       // 40 Bits Byte 3
  uint8_t brightness;           // 48 Bits Byte 4
  uint32_t period;              // 80 Bits Byte 5-8
} FunctionsCommsProtocol_t;

/**
 * @brief RGBControlCommsProtocol_t outlining byte packet structure for RGB control
 *
 */
typedef struct
{
  enum CTRL_CMD_ID command : 8; //  8 Bits Byte 0
  enum CHANNEL channel : 8;     // 16 Bits Byte 1
  enum FADE_TYPE mode : 8;      // 24 Bits Byte 2
  uint8_t redPWM;               // 32 Bits Byte 3
  uint8_t greenPWM;             // 40 Bits Byte 4
  uint8_t bluePWM;              // 48 Bits Byte 5
} RGBControlCommsProtocol_t;

/**
 * @brief HueControlCommsProtocol_t outlining byte packet structure for Hue control
 *
 */
typedef struct
{
  enum CTRL_CMD_ID command : 8; // 8 Bits Byte 0
  enum CHANNEL channel : 8;     // 8 Bits Byte 1
  enum FADE_TYPE mode : 8;      // 16 Bits Byte 2
  uint16_t hue;                 // 24 Bits Byte 3-4
  uint8_t saturation;           // 32 Bits Byte 5
  uint8_t brightness;           // 30 Bits Byte 6
} HueControlCommsProtocol_t;

/**
 * @brief UserModeSaveProtocol_t outlining byte packet structure for UserMode Saving
 *
 */
typedef struct
{
  enum CTRL_CMD_ID command : 8;                   // 8 Bits Byte 0
  uint8_t userModeNo;                             // 8 Bits Byte 1
  uint8_t userModePoints[USER_MODE_SLOT_SIZE]; // 8 Bits Byte 2- USER_MODE_END +3
} UserModeSaveProtocol_t;

/**
 * @brief UserModeChange_t outlining byte packet structure for UserMode changing
 *
 */
typedef struct
{
  enum CTRL_CMD_ID command : 8; // 8 Bits Byte 0
  enum CHANNEL channel : 8;     // 8 Bits Byte 1
  uint8_t userModeNo;           // 8 Bits Byte 2
} UserModeChange_t;
#endif