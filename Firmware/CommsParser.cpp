/**
 * @file CommsParser.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Communication Parser Implementation source code.
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "CommsParser.h"

// Internal Constants
const uint32_t SERIAL_BAUDRATE = 115200;
const uint8_t RX_LEN = commsPacketLength;

//Serial Comms Buffers
uint8_t rxBuff[RX_LEN]={0};

//Drivers
ColourDriver *colourDriver;
FadeDriver *fadeDriver;

// Internal Function Prototypes
void selectDrivers(enum CHANNEL channel);

/**
 * @brief Sets up the Communication channel
 * 
 */
void setupComms(void){
  Serial.begin(SERIAL_BAUDRATE);
  
}
/**
 * @brief Communication loop responsible for polling the UART USB Bus and deconstructing the received message and calling the apropriate drivers for fading and colour changes
 * 
 * | Channel | Mode | Colour | Brightness | PERIOD | 
 * @return |* 
 */
void commsLoop(void){
  
  if(Serial.available()>0){ 

      Serial.readBytes((char *)rxBuff,RX_LEN);
     //Fill C Message
      struct CommsProtocol_t messagePacket;
      messagePacket.channel = CHANNEL(rxBuff[0]);
      messagePacket.mode = FADE_TYPE(rxBuff[1]);
      messagePacket.colour = COLOUR(rxBuff[2]);
      messagePacket.brightness = rxBuff[3];
      messagePacket.period = (uint32_t)rxBuff[4]<<24 | (uint32_t)rxBuff[5]<<16 | (uint32_t)rxBuff[6]<<8 | (uint32_t)rxBuff[7];


      selectDrivers(messagePacket.channel);
      fadeDriver->startFade(messagePacket.mode,messagePacket.period,messagePacket.brightness);
      colourDriver->setColour(messagePacket.colour);
      if(messagePacket.mode == NONE){
        colourDriver->setBrightness(messagePacket.brightness);
      }
      
        Serial.print("Channel: "); Serial.println(messagePacket.channel);
        Serial.print("Mode: "); Serial.println(messagePacket.mode);
        Serial.print("Colour: "); Serial.println(messagePacket.colour);
        Serial.print("Brightness: "); Serial.println(messagePacket.brightness);
        Serial.print("Period: "); Serial.println(messagePacket.period);


  }


  
}

void selectDrivers(enum CHANNEL channel){
   switch(channel){
        case CHANNEL_1:
          colourDriver = stripOneDriver;
          fadeDriver= stripOneFadeDriver;
        break;
        case CHANNEL_2:
          colourDriver = stripTwoDriver;
          fadeDriver= stripTwoFadeDriver;
        break;
        case CHANNEL_3:
         colourDriver = stripThreeDriver;
          fadeDriver= stripThreeFadeDriver;
        break;
        case CHANNEL_NS:
        default:
          colourDriver = NULL;
          fadeDriver= NULL;
        break;
      }
}


