#ifndef __COMMS_PARSER_H__
#define __COMMS_PARSER_H__

#include <stdint.h>
#include <Arduino.h>


#include "ColourDriver.h"
#include "FadeDriver.h"
#include "Channels.h"
#include "Main.h"

extern void setupComms(void);
extern void commsLoop(void);

const uint8_t commsPacketLength = 8;

typedef struct CommsProtocol_t{
    enum CHANNEL channel:8; //8 Bits Byte 0
    enum FADE_TYPE mode:8;   //16 Bits Byte 1
    enum COLOUR colour:8;  //32 Bits Byte 2-3
    uint8_t brightness; //40 Bits Byte 4
    uint32_t period; //72 Bits Byte 5-7
};

union CommsMessage_t{ //This doesnt gaurantee alignmnet within program memory
  struct CommsProtocol_t commsPacket;
  uint8_t commsBytes[commsPacketLength];     
};


#endif