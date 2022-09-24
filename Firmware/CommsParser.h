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

const uint8_t commsPacketLength = 72 ;

typedef struct CommsProtocol_t{
    enum CHANNEL channel:8; //8 Byte 1
    enum FADE_TYPE mode:8;   //16 Byte 2
    enum COLOUR colour:16;  //32 Byte 3-4
    uint8_t brightness; //40 Byte 5
    uint32_t period; //72 Bytes Byte 6-9
};

union CommsMessage_t{
  struct CommsProtocol_t commsPacket;
  uint8_t commsBytes[commsPacketLength];     
};


#endif