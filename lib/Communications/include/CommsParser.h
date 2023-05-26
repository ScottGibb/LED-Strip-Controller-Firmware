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
#ifndef COMMS_PARSER_H
#define COMMS_PARSER_H



// Project Includes
#include "CommsStructures.h"
#include "ICommunicator.h"
#include "MemoryHandler.h"

// Library Includes
#include <stdint.h>
#include <vector>

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
    CommsParser(vector<ICommunicator *> comms, const uint32_t ledTxRate, const uint32_t pwrTxRate);
    /**
     * @brief Destroy the Comms Parser object
     *
     */
    ~CommsParser();
    /**
     * @brief Soft Timed loop for comm parsing
     *
     */
    void loop();

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
    void parseAndUpdate();
    /**
     * @brief Soft timed method that will send out periodic updates of what the LEDs are currently doing
     *
     */
    void sendLEDUpdate();
    /**
     * @brief Parses the buffer message concerning the led
     *
     */
    void ledChangeCommand();
    /**
     * @brief Saves a message for offline storage
     *
     */
    void saveMessage();
    /**
     * @brief Loads messages from offline storage
     */
    void loadMessages();
};

#endif//COMMS_PARSER_H