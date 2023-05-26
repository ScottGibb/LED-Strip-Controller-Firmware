/**
 * @file STM32F103C8T6MemoryMap.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief This file contains the preprocessor Memory Map for allocating the Flash memory for the LED Controller Project
 * @version 0.1
 * @date 2023-02-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef STM32F103C8T6_MEMORY_MAP_H
#define STM32F103C8T6_MEMORY_MAP_H

#include "CommsStructures.h"

#define EEPROM_SIZE 1024
/**
 * @brief Memory Subsegment Sizes
 *
 */
#define SYSTEM_INFO_MEM_SIZE 10

// Slot Sizes
#define SYSTEM_INFO_SLOT_SIZE 1
#define CHANNEL_CONTROL_SLOT_SIZE controlCommsPacketLength
#define USER_MODE_SLOT_SIZE 300

/**
 * @brief System Information Memory Segment
 *
 */
#define SYSTEM_INFO_START 0
#define NUM_SYSTEM_INFO (SYSTEM_INFO_MEM_SIZE / SYSTEM_INFO_SLOT_SIZE)
#define SYSTEM_INFO_END (SYSTEM_INFO_MEM_SIZE - 1)

/**
 * @brief Channel Control Memory Segment
 *
 */
#define CHANNEL_CONTROL_START SYSTEM_INFO_MEM_SIZE // Start Immediately after
#define NUM_CHANNEL_CONTROLS NUM_CHANNELS
#define CHANNEL_CONTROL_MEM_SIZE (CHANNEL_CONTROL_SLOT_SIZE * NUM_CHANNEL_CONTROLS)
#define CHANNEL_CONTROL_END ((CHANNEL_CONTROL_MEM_SIZE + SYSTEM_INFO_MEM_SIZE) - 1)

/**
 * @brief User Mode Memory Segment
 *
 */
#define USER_MODE_START (CHANNEL_CONTROL_MEM_SIZE + SYSTEM_INFO_MEM_SIZE)
#define NUM_USER_MODES ((EEPROM_SIZE - USER_MODE_START) / USER_MODE_SLOT_SIZE)
#define USER_MODE_MEM_SIZE (NUM_USER_MODES * USER_MODE_SLOT_SIZE)
#define USER_MODE_END ((USER_MODE_START + USER_MODE_MEM_SIZE) - 1)

/**
 * @brief End Address Memory Segment
 *
 */
#define END_ADDRESS (USER_MODE_START + (NUM_USER_MODES * USER_MODE_SLOT_SIZE))
#define DEAD_MEMORY (EEPROM_SIZE - END_ADDRESS)

#endif // STM32F103C8T6_MEMORY_MAP_H