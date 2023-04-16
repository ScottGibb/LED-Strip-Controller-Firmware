#include "SerialCommunicator.h"

// Library Includes
#include <stdint.h>
#include <Arduino.h>

#define CHOSEN_SERIAL Serial // USB Serial Selected

// Project Includes
SerialCommunicator::SerialCommunicator(uint32_t baudrate) : BAUDRATE(baudrate)
{
    CHOSEN_SERIAL.begin(BAUDRATE);
}
SerialCommunicator::~SerialCommunicator()
{
}
bool SerialCommunicator::loop(uint8_t *buff, uint8_t len)
{
    if (CHOSEN_SERIAL.available())
    {

        CHOSEN_SERIAL.readBytes((char *)buff, len);
        return true;
    }
    return false;
}
void SerialCommunicator::transmit(uint8_t *buff, uint8_t len)
{
    CHOSEN_SERIAL.write(buff, len);
}