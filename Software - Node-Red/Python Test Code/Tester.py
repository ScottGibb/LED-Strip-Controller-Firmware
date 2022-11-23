import struct

import serial

from Types import FADE_TYPE, CHANNEL, COLOUR

RX_MSG_CNT = 5
COM_PORT = 'COM5'
ser = serial.Serial(COM_PORT)
ser.parity = serial.PARITY_EVEN
ser.stopbits = serial.STOPBITS_ONE
ser.bytesize = serial.EIGHTBITS
while True:

    channel = int((input("Please Enter the Channel in which you would like to Change (1-3):")))
    colour = int(input("Please enter the colour you would like to have on this channel (0-12)"))
    mode = int(input("Please Enter the mode in which you would like to choose: (0-4)"))
    brightness = int(input("Please now select brightness: (0-100)"))
    period = 0
    if mode != FADE_TYPE.NONE.value:
        period = int(input("You have selected fading, please select the period of fading in ms"))

    # Construct Message
    tx_msg = bytearray([channel, mode, colour, brightness]) + period.to_bytes(4, "big")
    ser.write(tx_msg)
    print("Sent Message")
    print(tx_msg)
    print("Return Message:")
    for i in range(0, RX_MSG_CNT):
        print(ser.readline())
