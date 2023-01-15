#include "SerialCommunicator.h"

//Library Includes
#include <stdint.h>
#include <Arduino.h>

//Project Includes
SerialCommunicator::SerialCommunicator(uint32_t baudrate): BAUDRATE(baudrate)
{
    Serial.begin(BAUDRATE);
}
SerialCommunicator::~SerialCommunicator()
{
}
bool SerialCommunicator:: loop(uint8_t *buff, uint8_t len)
{
    if(Serial.available()){

        Serial.readBytes((char*)buff,len);
        return true;
    }
    return false;
}
void SerialCommunicator:: transmit(uint8_t *buff, uint8_t len)
{
    Serial.write(buff, len);
}