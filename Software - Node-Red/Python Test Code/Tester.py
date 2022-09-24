import struct

import serial

from Types import FADE_TYPE, CHANNEL, COLOUR

COM_PORT = 'COM1'
s = serial.Serial('COM1')

while True:

    channel = int((input("Please Enter the Channel in which you would like to Change (1-3):")))
    colour = (int(input("Please enter the colour you would like to have on this channel (0-13)")))
    mode = int(input("Please Enter the mode in which you would like to choose: (0-4)"))
    brightness = int(input("Please now select brightness: (0-100)"))
    period = 0
    if mode != FADE_TYPE.NONE.value:
        period = int(input("You have selected fading, please select the period of fading in ms"))

    # Construct Message
    tx_msg = bytes([channel, mode]) + struct.pack('>H', colour) + bytes([brightness]) + struct.pack('>I', period)
    print("Sent Message: " + str(tx_msg))
    s.write(tx_msg)
    print(s.readline())
