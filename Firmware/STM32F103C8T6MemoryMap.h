#ifndef STM32F103C8T6_MEMORY_MAP_H
#define STM32F103C8T6_MEMORY_MAP_H

#include "CommsStructures.h"

#define EEPROM_SIZE 1024
/**
 * @brief Memory Subsegment Sizes
 *
 */
#define SYSTEM_INFO_SIZE 10
#define CHANNEL_CONTROL_SIZE controlCommsPacketLength
#define USER_MODE_SEGMENT_SIZE 300

/**
 * @brief System Information Memory Segment
 *
 */
#define SYSTEM_INFO_START 0
#define SYSTEM_INFO_END (SYSTEM_INFO_SIZE-1)

/**
 * @brief Channel Control Memory Segment
 *
 */
#define CHANNEL_CONTROL_START SYSTEM_INFO_SIZE // Start Immediately after
#define CHANNEL_CONTROL_MEM_SIZE (CHANNEL_CONTROL_SIZE * NUM_CHANNELS)
#define CHANNEL_CONTROL_END ((CHANNEL_CONTROL_MEM_SIZE + SYSTEM_INFO_SIZE)-1)

/**
 * @brief User Mode Memory Segment
 *
 */
#define USER_MODE_START (CHANNEL_CONTROL_MEM_SIZE + SYSTEM_INFO_SIZE)
#define NUM_USER_MODES ((EEPROM_SIZE - USER_MODE_START) / USER_MODE_SEGMENT_SIZE)
#define USER_MODE_MEM_SIZE (NUM_USER_MODES*USER_MODE_SEGMENT_SIZE)
#define USER_MODE_END ((USER_MODE_START + USER_MODE_MEM_SIZE)-1)

/**
 * @brief End Address Memory Segment
 *
 */
#define END_ADDRESS (USER_MODE_START + (NUM_USER_MODES * USER_MODE_SEGMENT_SIZE))
#define DEAD_MEMORY (EEPROM_SIZE - END_ADDRESS)


#endif