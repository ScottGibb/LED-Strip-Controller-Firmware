#include <sys/types.h>
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

using namespace std;
// Library Includes
#include <Arduino.h>
#include <vector>
#include <stdint.h>
// Project Includes
#include "Main.h"
#include "HueDriver.h"
#include "LEDDriver.h"
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "ICommunicator.h"
#include "MemoryHandler.h"
#include "Channels.h"
/**
 * @brief Sets up the Communication channel
 *
 */
CommsParser::CommsParser(vector<ICommunicator*> comms, uint32_t ledTxRate, uint32_t pwrTxRate)
  : LED_TX_UPDATE_PERIOD(ledTxRate), PWR_TX_UPDATE_PERIOD(pwrTxRate) {
  this->comms = comms;

  memHandler = MemoryHandler::getInstance();

  if (memHandler == nullptr) {
    while (1)
      Serial.begin(115200);
    Serial.println("Im stuck here in Comms Parser!!");
  }


  loadMessages();
}

/**
 * @brief Responsible for calling send and receive functions
 *
 */
void CommsParser::loop(void) {
  for (uint8_t i = 0; i < comms.size(); i++) {
    if (comms[i]->loop(rxBuff, controlCommsPacketLength)) {  //Loop Through comms modules and check for updates
      //Message Received, parse and update
      parseAndUpdate();
      saveMessage();
    }
  }
  //Transmit Update Messages
  sendLEDUpdate();
}

/**
 * @brief Sets the colour and fade driver to the drivers associated with the channel
 * @param channel [in] the channel to be selected
 */
void CommsParser::selectDrivers(enum CHANNEL channel) {

  switch (channel) {
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

/**
 * @brief Communication loop responsible for polling the UART USB Bus and deconstructing the received message and calling the apropriate drivers for fading and colour changes
 *
 * | CTRL_CMD_ID | Channel | Mode | Colour | Brightness |   PERIOD   |
 * | CTRL_CMD_ID | Channel | Mode |  Red   |   Green    |    Blue    |
 * | CTRL_CMD_ID | Channel | Mode |  Hue   | Saturation | Brightness |
 * @return |*
 */
void CommsParser::parseAndUpdate(void) {
  switch ((CTRL_CMD_ID)rxBuff[0]) {
    case LED_CHANGE:
      ledChangeCommand();
      break;

    default:
      break;
  }
}

void CommsParser::ledChangeCommand(void) {
  CHANNEL channel = (CHANNEL)rxBuff[1];
  FADE_TYPE mode = (FADE_TYPE)rxBuff[2];
  selectDrivers(channel);
  if (channel == CHANNEL_NS) {
    return; // Return if no valid was selected!
  }
  switch (mode) {

    case RGB_CONTROL:
      uint8_t rgbLeds[NUM_LEDS];
      rgbLeds[0] = rxBuff[3];
      rgbLeds[1] = rxBuff[4];
      rgbLeds[2] = rxBuff[5];
      fadeDriver->stopFade();  //Start in RGB Mode, Fade Driver is essentially disabled
      ledDriver->setPWMS(rgbLeds);
      break;

    case HUE_CONTROL:
      {
        HSV_t hsv = {
          .hue = ((uint16_t)rxBuff[3] << 8 | (uint16_t)rxBuff[4]) * 1.0f,
          .saturation = rxBuff[5] * 1.0f,
          .value = rxBuff[6] * 1.0f
        };
        fadeDriver->stopFade();
        hueDriver->setHue(hsv);
      }
      break;
    default:

      COLOUR colour = COLOUR(rxBuff[3]);
      uint8_t brightness = rxBuff[4];
      uint32_t period = (uint32_t)rxBuff[5] << 24 | (uint32_t)rxBuff[6] << 16 | (uint32_t)rxBuff[7] << 8 | (uint32_t)rxBuff[8];


      fadeDriver->startFade(mode, period, brightness); 
      colourDriver->setColour(colour);
      if (mode == NONE) {
        colourDriver->setBrightness(brightness);
      }
  }
}
/**
 * @brief sends out an update regarding the LED system
 * | UPDATE ID | Arguments |
 * | UPDATE ID |  NUM LEDS | LED NUM |  RED  | GREEN | BLUE | XXXX
 *
 */
void CommsParser::sendLEDUpdate(void) {
  if (millis() - lastLedTxUpdate > LED_TX_UPDATE_PERIOD) {
    txBuff[0] = LED_UPDATE;
    uint8_t numLeds = leds.size();
    txBuff[1] = numLeds;

    for (uint8_t i = 0; i < numLeds; i++) {
      uint8_t arrayPos = (i * numLeds) + 2;
      txBuff[arrayPos] = i;
      for (uint8_t j = 0; j < numLeds; j++) {
        txBuff[++arrayPos] = leds[j]->getPWM(LED_COLOUR(i)) && (0xFF000000 >> 24);
        txBuff[++arrayPos] = leds[j]->getPWM(LED_COLOUR(i)) && (0x00FF0000 >> 16);
        txBuff[++arrayPos] = leds[j]->getPWM(LED_COLOUR(i)) && (0x0000FF00 >> 8);
        txBuff[++arrayPos] = leds[j]->getPWM(LED_COLOUR(i)) && (0x000000FF);
      }
    }
    for (uint8_t i = 0; i < comms.size(); i++) {
      comms[i]->transmit(txBuff, telemetryCommsPacketLength);
    }
    lastLedTxUpdate = millis();
  }
}

void CommsParser::saveMessage(void) {
  CHANNEL channel = (CHANNEL)rxBuff[1];
  uint8_t savePos = static_cast<uint8_t>(channel) - 1;
  memHandler->saveData(SEGMENT::CHANNEL_CMDS, savePos, rxBuff, controlCommsPacketLength);
}

void CommsParser::loadMessages(void) {
  for (uint8_t i = 0; i < leds.size(); i++) {
    memHandler->loadData(SEGMENT::CHANNEL_CMDS, i, rxBuff, controlCommsPacketLength);
    parseAndUpdate();
  }
}