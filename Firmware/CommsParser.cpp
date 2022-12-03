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

//Library Includes
#include <Arduino.h>
#include <stdint.h>
//Project Includes
#include "Main.h"
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "Channels.h"

// Internal Constants
static const uint32_t SERIAL_BAUDRATE = 115200;
static const uint8_t RX_LEN = commsPacketLength;

//Serial Comms Buffers
static uint8_t rxBuff[RX_LEN] = { 0 };


//Drivers
static RGBColourDriver *colourDriver;
static FadeDriver *fadeDriver;
static HueDriver *hueDriver;
static LEDDriver *ledDriver;

// Internal Function Prototypes
void selectDrivers(enum CHANNEL channel);

/**
 * @brief Sets up the Communication channel
 * 
 */
void setupComms(void) {
  Serial.begin(SERIAL_BAUDRATE);
}
/**
 * @brief Communication loop responsible for polling the UART USB Bus and deconstructing the received message and calling the apropriate drivers for fading and colour changes
 * 
 * | Channel | Mode | Colour | Brightness | PERIOD | 
 * | Channel | Mode |  Red   |   Green    |  Blue  |
 * @return |* 
 */
void commsLoop(void) {

  if (Serial.available() > 0) {

    Serial.readBytes((char *)rxBuff, RX_LEN);
    //Fill C Message
    FunctionsCommsProtocol_t functionsMessagePacket;
    RGBControlCommsProtocol_t rgbMessagePacket;
    HueControlCommsProtocol_t hueMessagePacket;

    functionsMessagePacket.channel = CHANNEL(rxBuff[0]);
    rgbMessagePacket.channel = CHANNEL(rxBuff[0]);
    hueMessagePacket.channel = CHANNEL(rxBuff[0]);

    functionsMessagePacket.mode = FADE_TYPE(rxBuff[1]);
    rgbMessagePacket.mode = FADE_TYPE(rxBuff[1]);
    hueMessagePacket.mode = FADE_TYPE(rxBuff[1]);

    selectDrivers(functionsMessagePacket.channel);

    switch (functionsMessagePacket.mode) {

      case RGB_CONTROL:
        rgbMessagePacket.redPWM = rxBuff[2];
        rgbMessagePacket.greenPWM = rxBuff[3];
        rgbMessagePacket.bluePWM = rxBuff[4];
        uint8_t leds[3];
        leds[0] = rgbMessagePacket.redPWM;
        leds[1] = rgbMessagePacket.greenPWM;
        leds[2] = rgbMessagePacket.bluePWM;
        ledDriver->setPWMS(leds);
        break;
      case HUE_CONTROL:
        hueMessagePacket.hue =  (float)((uint32_t)rxBuff[2] << 24 | (uint32_t)rxBuff[3] << 16 | (uint32_t)rxBuff[4] << 8 | (uint32_t)rxBuff[5]);
        hueMessagePacket.saturation =  (float)((uint32_t)rxBuff[6] << 24 | (uint32_t)rxBuff[7] << 16 | (uint32_t)rxBuff[8] << 8 | (uint32_t)rxBuff[9]);
        hueMessagePacket.brightness =  (float)((uint32_t)rxBuff[10] << 24 | (uint32_t)rxBuff[11] << 16 | (uint32_t)rxBuff[12] << 8 | (uint32_t)rxBuff[13]);
        HSB_t hsb;
        hsb.hue= hueMessagePacket.hue;
        hsb.saturation = hueMessagePacket.saturation;
        hsb.brightness = hueMessagePacket.brightness;
        hueDriver->setHue(hsb);
        break;

      default:
        functionsMessagePacket.colour = COLOUR(rxBuff[2]);
        functionsMessagePacket.brightness = rxBuff[3];
        functionsMessagePacket.period = (uint32_t)rxBuff[4] << 24 | (uint32_t)rxBuff[5] << 16 | (uint32_t)rxBuff[6] << 8 | (uint32_t)rxBuff[7];

        fadeDriver->startFade(functionsMessagePacket.mode, functionsMessagePacket.period, functionsMessagePacket.brightness);
        colourDriver->setColour(functionsMessagePacket.colour);
        if (functionsMessagePacket.mode == NONE) {
          colourDriver->setBrightness(functionsMessagePacket.brightness);
        }
    }

    Serial.print("Channel: ");
    Serial.println(functionsMessagePacket.channel);
    Serial.print("Mode: ");
    Serial.println(functionsMessagePacket.mode);
    Serial.print("Colour: ");
    Serial.println(functionsMessagePacket.colour);
    Serial.print("Brightness: ");
    Serial.println(functionsMessagePacket.brightness);
    Serial.print("Period: ");
    Serial.println(functionsMessagePacket.period);
  }
}

/**
 * @brief Sets the colour and fade driver to the drivers associated with the channel
 * @param channel [in] the channel to be selected
 */
void selectDrivers(enum CHANNEL channel) {
  switch (channel) {
    case CHANNEL_1:
      ledDriver = ledOne;
      hueDriver = stripOneHueDriver;
      colourDriver = stripOneDriver;
      fadeDriver = stripOneFadeDriver;
      break;
    case CHANNEL_2:
      ledDriver = ledTwo;
      hueDriver = stripTwoHueDriver;
      colourDriver = stripTwoDriver;
      fadeDriver = stripTwoFadeDriver;
      break;
    case CHANNEL_3:
      ledDriver = ledThree;
      hueDriver = stripThreeHueDriver;
      colourDriver = stripThreeDriver;
      fadeDriver = stripThreeFadeDriver;
      break;
    case CHANNEL_NS:
    default:
      ledDriver = NULL;
      hueDriver = NULL;
      colourDriver = NULL;
      fadeDriver = NULL;
      break;
  }
}