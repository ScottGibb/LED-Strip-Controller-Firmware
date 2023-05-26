#ifndef ICOMMUNICATOR_H
#define ICOMMUNICATOR_H
// Library Includes
#include <stdint.h>
/**
 * @brief Interface defining low level communicators
 *
 */
class ICommunicator
{

public:
    /**
     * @brief soft polling loop in which a buffer is updated along with the amount of bytes to wait for
     *
     * @param buff the buffer containing the command packet
     * @param len the length of the expected command packet
     * @return true if message was available
     * @return false if no message was available
     */
    virtual bool loop(uint8_t *buff, uint8_t len) = 0;
    /**
     * @brief Transmits the selected message stored in buff
     *
     * @param buff the tx buffer
     * @param len the length of the message
     */
    virtual void transmit(uint8_t *buff, uint8_t len) = 0;
};

#endif//ICOMMUNICATOR_H