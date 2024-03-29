
#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

// Library Includes
#include <stdint.h>

// Project Includes

#include "ICommunicator.h"

/**
 * @brief SerialCommunicator Low level class concerned with interacting with the UART hardware and transmitting bytes
 *
 */
class SerialCommunicator : public ICommunicator
{
public:
    /**
     * @brief Construct a new Serial Communicator object
     *
     * @param BAUDRATE the selected baudrate
     */
    SerialCommunicator(uint32_t BAUDRATE);
    /**
     * @brief Destroy the Serial Communicator object
     *
     */
    ~SerialCommunicator();

    bool loop(uint8_t *buff, uint8_t len);
    void transmit(uint8_t *buff, uint8_t len);

private:
    const uint32_t BAUDRATE;
};
#endif