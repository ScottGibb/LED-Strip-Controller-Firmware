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

// Project Includes
#include "CommsStructures.h"

class CommsParser
{
public:
    CommsParser(uint32_t baudrate, uint32_t ledTxUpdatePeriod);
    ~CommsParser();
    void loop();

private:
    // Internal Constants
    const uint32_t SERIAL_BAUDRATE;
    static constexpr uint8_t RX_LEN = controlCommsPacketLength;
    static constexpr uint8_t TX_LEN = telemetryCommsPacketLength;
    // Drivers
    RGBColourDriver *colourDriver;
    FadeDriver *fadeDriver;
    HueDriver *hueDriver;
    LEDDriver *ledDriver;
    // Update Rates
    const uint32_t LED_TX_UPDATE_PERIOD;
    uint32_t lastLedTxUpdate = 0;
    // Serial Comms Buffers
    uint8_t rxBuff[RX_LEN] = {0};
    uint8_t txBuff[TX_LEN] = {0};

    void selectDrivers(enum CHANNEL channel);
    void receiveUpdate(void);
    void parseAndUpdate(void);
    void sendLEDUpdate(void);
};

#endif