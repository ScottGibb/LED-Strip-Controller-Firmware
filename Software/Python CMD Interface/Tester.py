# Imports
import struct
import threading
import binascii
# import serial

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
    """_summary_: Adds padding to the message to ensure that the message is the correct size
    """
    global tx_msg
    padding_len = TX_MSG_SIZE - len(tx_msg)
    if padding_len > 0:
        tx_msg = tx_msg + bytearray([0] * padding_len)

def check_bounds(val, min_val, max_val):
    """_summary_: Checks if a value is within the bounds of a min and max value
    _params_: val: The value to check
              min_val: The minimum value
              max_val: The maximum value
    _return_: True if the value is within the bounds, False otherwise
    """
    try:
        val = int(val)

    except ValueError:
        print("Invalid Value for value, please try again")
        return False
    
    if val < min_val or val > max_val:
        print("Value out of bounds, please try again inside the bounds of " + str(min_val) + " and " + str(max_val))
        return False
    return True

def ask_user(message, bounds):
    """_summary_: Asks the user for input and checks if the input is within the bounds, blocks until the user enters a valid input

    Args:
        message (_type_): _description_ The message to display to the user
        bounds (_type_): _description_ The bounds to check the input against
    Returns:
        _type_: _description_ The user input if it is within the bounds otherwise it will ask the user again
    """
    while(True):
        user_input = input(message)
        if check_bounds(user_input, bounds.get("START"), bounds.get("END")):
            return user_input
        else:
            print("Invalid: Please try again")
    
def create_hue_message(channel, mode):
    """_summary_: Gets the message to send to the hardware to change the hue mode
    Args:
        channel (_type_): _description_ The channel to change
        mode (_type_): _description_ The mode to change to
    Returns:
        _type_: _description_ The message to send to the hardware
    """
    user_bounds = {"START": 0, "END": 360}
    user_message = "Please select the Hue value you would like to choose: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    hue = int(ask_user(user_message, user_bounds))

    user_bounds = {"START": 0, "END": 100}
    user_message = "Please select the Saturation value you would like to choose: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    saturation = int(ask_user(user_message, user_bounds))

    user_message = "Please select the Brightness value you would like to choose: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    brightness = int(ask_user(user_message, user_bounds))
    hue_bytes = hue.to_bytes(2, 'big')
    bytes = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel, mode]) + hue_bytes + bytearray([saturation, brightness])
    return bytes

def create_rgb_message(channel, mode):
    """_summary_: Gets the message to send to the hardware to change the rgb mode
    Args:
        channel (_type_): _description_ The channel to change
        mode (_type_): _description_ The mode to change to
    Returns:
        _type_: _description_ The message to send to the hardware
    """
    user_bounds = {"START": 0, "END": 255}
    user_message = "Please select the Red value you would like to choose: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    red = int(ask_user(user_message, user_bounds))

    user_message = "Please select the Green value you would like to choose: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    green = int(ask_user(user_message, user_bounds))

    user_message = "Please select the Blue value you would like to choose: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    blue = int(ask_user(user_message, user_bounds))
    bytes = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel, mode, red, green, blue])
    return bytes

def create_colour_message(channel, mode):
    """_summary_: Gets the message to send to the hardware to change the colour mode
    Args:
        channel (_type_): _description_ The channel to change
        mode (_type_): _description_ The mode to change to
        colour (_type_): _description_ The colour to change to
        brightness (_type_): _description_ The brightness to change to
    Returns:
        _type_: _description_ The message to send to the hardware
    """
    user_bounds = {"START": 0, "END": 12}
    user_message = "Please select the colour you would like to have on this channel: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    colour = int(ask_user(user_message, user_bounds))

    user_bounds = {"START": 0, "END": 100}
    user_message = "Please select the brightness you would like to have on this channel: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    brightness = int(ask_user(user_message, user_bounds))
    period = 0
    if mode != FADE_TYPE.NONE.value:
        user_bounds = {"START": 0, "END": 4294967295}
        user_message = "Please select the period of the fade in ms: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
        period = int(ask_user(user_message, user_bounds))
    bytes = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel, mode, colour, brightness])+ period.to_bytes(4, "big")
    return bytes



while True:
    """_summary_: The main loop of the program, asks the user for input and sends the message to the hardware
    """
    tx_msg = None

    # Ask user for channel
    user_bounds = {"START": 0, "END": 3}
    user_message = "Please select the channel you would like to change: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    channel = int(ask_user(user_message, user_bounds))

    # Ask user for mode
    user_bounds = {"START": 0, "END": 7}
    user_message = "Please select the mode you would like to choose: ("+str(user_bounds.get("START"))+ " - "+str(user_bounds.get("END"))+")"
    mode = int(ask_user(user_message, user_bounds))

    if mode == FADE_TYPE.HUE_CTRL.value:
        tx_msg = create_hue_message(channel, mode)
    elif mode == FADE_TYPE.RGB_CTRL.value:
        tx_msg = create_rgb_message(channel, mode)
    else:
        tx_msg = create_colour_message(channel, mode)

    # Add padding to the message and send it
    add_padding()
    ser.write(tx_msg)
    print("Sent Message")
    print(binascii.hexlify(tx_msg))
