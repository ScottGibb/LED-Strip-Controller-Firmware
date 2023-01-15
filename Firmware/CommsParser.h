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

// Library Includes
#include <stdint.h>
#include <vector>
// Project Includes
#include "CommsStructures.h"
#include "ICommunicator.h"

class CommsParser
{
public:
    CommsParser(vector<ICommunicator*> comms, uint32_t ledTxRate, uint32_t pwrTxRate);
    ~CommsParser();
    void loop();

private:
    vector<ICommunicator*> comms;
   // Serial Comms Buffers
    uint8_t rxBuff[controlCommsPacketLength] = {0};
    uint8_t rxLen=0;
    uint8_t txBuff[telemetryCommsPacketLength] = {0};
    uint8_t txLen =0;
    // Drivers
    RGBColourDriver *colourDriver;
    FadeDriver *fadeDriver;
    HueDriver *hueDriver;
    LEDDriver *ledDriver;

    // Update Rates
    const uint32_t LED_TX_UPDATE_PERIOD;
    uint32_t lastLedTxUpdate;
    const uint32_t PWR_TX_UPDATE_PERIOD;
    uint32_t lastPwrUpdate;


    void selectDrivers(enum CHANNEL channel);
    void parseAndUpdate(void);
    void sendLEDUpdate(void);
};

#endif