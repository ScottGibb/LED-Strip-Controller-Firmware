# Imports
import struct
import serial

from Types import FADE_TYPE, CHANNEL, COLOUR

# Serial Variables
RX_MSG_CNT = 5
COM_PORT = input("What port is the hardware connected on?")

ser = serial.Serial(COM_PORT)
ser.parity = serial.PARITY_EVEN
ser.stopbits = serial.STOPBITS_ONE
ser.bytesize = serial.EIGHTBITS

## Main Loop
while True:
    tx_msg = None
    channel = int((input("Please Enter the Channel in which you would like to Change (1-3):")))
    mode = int(input("Please Enter the mode in which you would like to choose: (0-6)"))
    if mode == FADE_TYPE.HUE_CTRL.value:
        hue = float(input("Please enter the Hue value (0.0-360.0)"))
        saturation = float(input("Please enter the Hue value (0.0-1.0)"))
        brightness = float(input("Please enter the Hue value (0.0-1.0)"))
        tx_msg = bytearray([channel, mode]) + struct.pack("f", hue) + struct.pack("f", saturation) + struct.pack("f",
                                                                                                                 brightness)

    elif mode == FADE_TYPE.RGB_CTRL.value:
        redPWM = int(input("Pleas enter the red value (0-255"))
        greenPWM = int(input("Pleas enter the green value (0-255"))
        bluePWM = int(input("Pleas enter the blue value (0-255"))
        tx_msg = bytearray([channel, mode, redPWM, greenPWM, bluePWM])
    else:
        colour = int(input("Please enter the colour you would like to have on this channel (0-12)"))
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
