# Imports
import struct
import threading
import binascii
import serial

from Types import FADE_TYPE, CHANNEL, COLOUR, CTRL_CMD_ID

# Serial Variables
RX_MSG_CNT = 14
TX_MSG_SIZE = 10
COM_PORT = input("What port is the hardware connected on?")

ser = serial.Serial(COM_PORT)
ser.parity = serial.PARITY_EVEN
ser.timeout = 1
ser.stopbits = serial.STOPBITS_ONE
ser.bytesize = serial.EIGHTBITS


def add_padding():
    global tx_msg
    padding_len = TX_MSG_SIZE - len(tx_msg)
    if padding_len > 0:
        tx_msg = tx_msg + bytearray([0] * padding_len)


## Main Loop
while True:
    tx_msg = None

    channel = int((input("Please Enter the Channel in which you would like to Change (1-3):")))
    mode = int(input("Please Enter the mode in which you would like to choose: (0-7)"))
    if mode == FADE_TYPE.HUE_CTRL.value:
        hue = int(input("Please enter the Hue value (0.0-360.0)"))
        saturation = int(input("Please enter the Saturation value (0-100)"))
        brightness = int(input("Please enter the Brightness value (0-100)"))
        hue_bytes = hue.to_bytes(2, 'big')
        tx_msg = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel, mode]) + hue_bytes + bytearray([saturation, brightness])
    elif mode == FADE_TYPE.RGB_CTRL.value:
        redPWM = int(input("Pleas enter the red value (0-255)"))
        greenPWM = int(input("Pleas enter the green value (0-255)"))
        bluePWM = int(input("Pleas enter the blue value (0-255)"))
        tx_msg = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel, mode, redPWM, greenPWM, bluePWM])
    else:
        colour = int(input("Please enter the colour you would like to have on this channel (0-12)"))
        brightness = int(input("Please now select brightness: (0-100)"))
        period = 0
        if mode != FADE_TYPE.NONE.value:
            period = int(input("You have selected fading, please select the period of fading in ms"))

        # Construct Message
        tx_msg = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel, mode, colour, brightness]) + period.to_bytes(4, "big")

    add_padding()
    ser.write(tx_msg)
    print("Sent Message")
    print(binascii.hexlify(tx_msg))
