#include "CommsParser.h"


void selectDrivers(enum CHANNEL channel);

const uint32_t SERIAL_BAUDRATE = 115200;
const uint8_t RX_LEN = commsPacketLength;

//Serial Comms Buffers
uint8_t rxBuff[RX_LEN]={0};

//Drivers
ColourDriver *colourDriver;
FadeDriver *fadeDriver;

void setupComms(void){
  Serial.begin(SERIAL_BAUDRATE);
}
/**
| Channel | Mode | Colour | Brightness | PERIOD | 
**/
void commsLoop(void){
  if(Serial.available()>0){
      Serial.readBytes((char *)rxBuff,RX_LEN);
      union CommsMessage_t message;
     for(uint8_t index = 0; index < RX_LEN; index++){
       message.commsBytes[index] = rxBuff[index];
     }
      
      struct CommsProtocol_t messagePacket = message.commsPacket;
      selectDrivers(messagePacket.channel);
      fadeDriver->startFade(messagePacket.mode,messagePacket.period,messagePacket.brightness);
      colourDriver->setColour(messagePacket.colour);
      if(messagePacket.mode != NONE){
        colourDriver->setBrightness(messagePacket.brightness);
      }
        //System Feedback message
        Serial.print("Channel: "); Serial.println(messagePacket.channel);
        Serial.print("Mode: "); Serial.println(messagePacket.mode);
        Serial.print("Colour: "); Serial.println(messagePacket.colour);
        Serial.print("Brightness: "); Serial.println(messagePacket.brightness);

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


