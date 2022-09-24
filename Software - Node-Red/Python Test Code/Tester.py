import struct

import serial

from Types import FADE_TYPE, CHANNEL, COLOUR

COM_PORT = 'COM4'
s = serial.Serial(COM_PORT)
s.parity = serial.PARITY_EVEN
s.stopbits = serial.STOPBITS_ONE
s.bytesize = serial.EIGHTBITS
while True:

    channel = int((input("Please Enter the Channel in which you would like to Change (1-3):")))
    colour = (int(input("Please enter the colour you would like to have on this channel (0-13)")))
    mode = int(input("Please Enter the mode in which you would like to choose: (0-4)"))
    brightness = int(input("Please now select brightness: (0-100)"))
    period = 0
    if mode != FADE_TYPE.NONE.value:
        period = int(input("You have selected fading, please select the period of fading in ms"))

    # Construct Message
    tx_msg = bytearray([channel, mode]) + struct.pack('<H', colour)
    tx_msg.extend(bytearray([brightness]))
    tx_msg.extend(struct.pack('<L',period))

    s.write(tx_msg)
    for byte in tx_msg:
        print(byte)
    print("Sent Message: " + str(tx_msg))
    print(s.readline())
    print(s.readline())
    print(s.readline())
    print(s.readline())
    print(s.readline())

