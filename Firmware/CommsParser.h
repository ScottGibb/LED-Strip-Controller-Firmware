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
    enum CHANNEL channel; //8
    enum FADE_TYPE mode;   //16
    enum COLOUR colour;  //32
    uint8_t brightness; //40
    uint32_t period; //72 Bytes
};

union CommsMessage_t{
  struct CommsProtocol_t commsPacket;
  uint8_t commsBytes[commsPacketLength];     
};


#endif