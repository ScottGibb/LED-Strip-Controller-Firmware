#include "SerialCommunicator.h"

//Library Includes
#include <stdint.h>
#include <Arduino.h>

#define SERIAL Serial //USB Serial Selected

//Project Includes
SerialCommunicator::SerialCommunicator(uint32_t baudrate): BAUDRATE(baudrate)
{
    SERIAL.begin(BAUDRATE);
}
SerialCommunicator::~SerialCommunicator()
{
}
bool SerialCommunicator:: loop(uint8_t *buff, uint8_t len)
{
    if(SERIAL.available()){
         
        SERIAL.readBytes((char*)buff,len);
        return true;
    }
    return false;
}
void SerialCommunicator:: transmit(uint8_t *buff, uint8_t len)
{
    SERIAL.write(buff, len);
}