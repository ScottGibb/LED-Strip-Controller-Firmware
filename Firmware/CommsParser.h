/**
 * @file CommsParser.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief CommsParser Header File for used with UART communication over USB
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __COMMS_PARSER_H__
#define __COMMS_PARSER_H__

//Library Includes
#include <stdint.h>
#include <Arduino.h>

//Project Includes
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "Channels.h"
#include "Main.h"

//External Constants
const uint8_t commsPacketLength = 8;

//External Function Prototypes
extern void setupComms(void);
extern void commsLoop(void);

/**
 * @brief Commmunication Protocol Struct used to outline the Comms Packet being sent to the MCU for control of the system.
 * 
 */
typedef struct CommsProtocol_t{
    enum CHANNEL channel:8; //8 Bits Byte 0
    enum FADE_TYPE mode:8;   //16 Bits Byte 1
    enum COLOUR colour:8;  //32 Bits Byte 2-3
    uint8_t brightness; //40 Bits Byte 4
    uint32_t period; //72 Bits Byte 5-7
};

/**
 * @brief Comms Message Union used to represent the byte array as a struct
 * 
 */
union CommsMessage_t{ //This doesnt gaurantee alignmnet within program memory
  struct CommsProtocol_t commsPacket;
  uint8_t commsBytes[commsPacketLength];     
};


#endif