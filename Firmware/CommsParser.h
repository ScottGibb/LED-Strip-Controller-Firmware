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
#include "MemoryHandler.h"

/**
 * @brief CommsParser class concerned with byte level parsing and updating the corresponding drivers
 *
 */
class CommsParser
{
public:
    /**
     * @brief Construct a new Comms Parser object
     *
     * @param comms a vector containing the corresponding communicator objects
     * @param ledTxRate //the rate in ms in which led update messages will be sent
     * @param pwrTxRate //the rate in ms in which pwr update messages will be sent
     */
    CommsParser(vector<ICommunicator *> comms, uint32_t ledTxRate, uint32_t pwrTxRate);
    /**
     * @brief Destroy the Comms Parser object
     *
     */
    ~CommsParser();
    /**
     * @brief Soft Timed loop for comm parsing
     *
     */
    void loop(void);

private:
    vector<ICommunicator *> comms;
    // Serial Comms Buffers
    uint8_t rxBuff[controlCommsPacketLength] = {0};
    uint8_t rxLen = 0;
    uint8_t txBuff[telemetryCommsPacketLength] = {0};
    uint8_t txLen = 0;
    // Drivers
    RGBColourDriver *colourDriver;
    FadeDriver *fadeDriver;
    HueDriver *hueDriver;
    LEDDriver *ledDriver;
    MemoryHandler *memHandler;
    // Update Rates
    const uint32_t LED_TX_UPDATE_PERIOD;
    uint32_t lastLedTxUpdate;
    const uint32_t PWR_TX_UPDATE_PERIOD;
    uint32_t lastPwrUpdate;

    /**
     * @brief Selects the driver that will be updated
     *
     * @param channel the channel to be chosen
     */
    void selectDrivers(enum CHANNEL channel);
    /**
     * @brief Parses the incoming message and updates the corresponding drivers
     *
     */
    void parseAndUpdate(void);
    /**
     * @brief Soft timed method that will send out periodic updates of what the LEDs are currently doing
     *
     */
    void sendLEDUpdate(void);
    /**
     * @brief Parses the buffer message concerning the led
     *
     */
    void ledChangeCommand(void);
    /**
     * @brief Saves a message for offline storage
     *
     */
    void saveMessage(void);
    /**
     * @brief Loads messages from offline storage
     */
    void loadMessages(void);
};

#endif