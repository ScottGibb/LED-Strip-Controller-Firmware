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

// Library Includes
#include <Arduino.h>
#include <stdint.h>
// Project Includes
#include "Main.h"
#include "HueDriver.h"
#include "LEDDriver.h"
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "StateSaver.h"
#include "Channels.h"

/**
 * @brief Sets up the Communication channel
 *
 */
CommsParser::CommsParser(uint32_t baudrate, uint32_t ledTxUpdatePeriod) : SERIAL_BAUDRATE{baudrate}, LED_TX_UPDATE_PERIOD{ledTxUpdatePeriod}
{
  Serial.begin(SERIAL_BAUDRATE);
}

/**
 * @brief Responsible for calling send and receive functions
 *
 */
void CommsParser::loop(void)
{

  receiveUpdate();
  sendLEDUpdate();
}

/**
 * @brief Sets the colour and fade driver to the drivers associated with the channel
 * @param channel [in] the channel to be selected
 */
void CommsParser::selectDrivers(enum CHANNEL channel)
{
  switch (channel)
  {
  case CHANNEL_1:
  case CHANNEL_2:
  case CHANNEL_3:
    ledDriver = leds[channel - 1];
    hueDriver = hueDrivers[channel - 1];
    colourDriver = stripDrivers[channel - 1];
    fadeDriver = fadeDrivers[channel - 1];
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

void CommsParser::receiveUpdate(void)
{
  if (Serial.available() > 0)
  {

    Serial.readBytes((char *)rxBuff, RX_LEN);
    parseAndUpdate();
  }
}
/**
 * @brief Communication loop responsible for polling the UART USB Bus and deconstructing the received message and calling the apropriate drivers for fading and colour changes
 *
 * | Channel | Mode | Colour | Brightness |   PERIOD   |
 * | Channel | Mode |  Red   |   Green    |    Blue    |
 * | Channel | Mode |  Hue   | Saturation | Brightness |
 * @return |*
 */
void CommsParser::parseAndUpdate(void)
{

  // Fill C Message
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

  switch (functionsMessagePacket.mode)
  {

  case RGB_CONTROL:
    rgbMessagePacket.redPWM = rxBuff[2];
    rgbMessagePacket.greenPWM = rxBuff[3];
    rgbMessagePacket.bluePWM = rxBuff[4];
    uint8_t leds[3];
    leds[0] = rgbMessagePacket.redPWM;
    leds[1] = rgbMessagePacket.greenPWM;
    leds[2] = rgbMessagePacket.bluePWM;
    fadeDriver->stopFade();
    ledDriver->setPWMS(leds);
    break;
  case HUE_CONTROL:
    hueMessagePacket.hue = (float)((uint32_t)rxBuff[2] << 24 | (uint32_t)rxBuff[3] << 16 | (uint32_t)rxBuff[4] << 8 | (uint32_t)rxBuff[5]);
    hueMessagePacket.saturation = (float)((uint32_t)rxBuff[6] << 24 | (uint32_t)rxBuff[7] << 16 | (uint32_t)rxBuff[8] << 8 | (uint32_t)rxBuff[9]);
    hueMessagePacket.brightness = (float)((uint32_t)rxBuff[10] << 24 | (uint32_t)rxBuff[11] << 16 | (uint32_t)rxBuff[12] << 8 | (uint32_t)rxBuff[13]);
    HSB_t hsb;
    hsb.hue = hueMessagePacket.hue;
    hsb.saturation = hueMessagePacket.saturation;
    hsb.brightness = hueMessagePacket.brightness;
    fadeDriver->stopFade();
    hueDriver->setHue(hsb);
    break;

  default:
    functionsMessagePacket.colour = COLOUR(rxBuff[2]);
    functionsMessagePacket.brightness = rxBuff[3];
    functionsMessagePacket.period = (uint32_t)rxBuff[4] << 24 | (uint32_t)rxBuff[5] << 16 | (uint32_t)rxBuff[6] << 8 | (uint32_t)rxBuff[7];

    fadeDriver->startFade(functionsMessagePacket.mode, functionsMessagePacket.period, functionsMessagePacket.brightness);
    colourDriver->setColour(functionsMessagePacket.colour);
    if (functionsMessagePacket.mode == NONE)
    {
      colourDriver->setBrightness(functionsMessagePacket.brightness);
    }
  }
}

/**
 * @brief sends out an update regarding the system
 * | UPDATE ID | Arguments |
 * | UPDATE ID |  NUM LEDS | LED NUM |  RED  | GREEN | BLUE | XXXX
 *
 */
void CommsParser::sendLEDUpdate(void)
{
  if (millis() - lastLedTxUpdate > LED_TX_UPDATE_PERIOD)
  {
    txBuff[0] = LED_UPDATE;

    for (uint8_t i = 0; i < leds.size(); i++)
    {
      uint8_t arrayPos = (i * NUM_LEDS) + 1;
      txBuff[arrayPos] = i;
      for (uint8_t j = 0; j < NUM_LEDS; j++)
      {
        txBuff[++arrayPos] = leds[j]->getPWM(LED_COLOUR(i)) && (0xFF000000 >> 24);
        txBuff[++arrayPos] = leds[j]->getPWM(LED_COLOUR(i)) && (0x00FF0000 >> 16);
        txBuff[++arrayPos] = leds[j]->getPWM(LED_COLOUR(i)) && (0x0000FF00 >> 8);
        txBuff[++arrayPos] = leds[j]->getPWM(LED_COLOUR(i)) && (0x000000FF);
      }
    }
    Serial.write(txBuff,telemetryCommsPacketLength);
    lastLedTxUpdate = millis();
  }
}