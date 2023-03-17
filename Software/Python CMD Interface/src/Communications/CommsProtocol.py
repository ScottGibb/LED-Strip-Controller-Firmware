# This Python file contains the methods required to interact with the hardware by creating the desired byte packet using the Types.py file and then sending it to the hardware using the CommsProtocol.py file.

from Types import COLOUR, CTRL_CMD_ID
from Types import CHANNEL
from Types import FADE_TYPE
from Types import TX_MSG_SIZE


def create_constant_colour_message(channel: CHANNEL, colour: COLOUR, brightness):
    bytes = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel.value,
                       FADE_TYPE.NONE, colour, brightness])
    return _add_padding(bytes)


def create_fade_message(channel: CHANNEL, fade_type: FADE_TYPE, colour: COLOUR, brightness, period):
    bytes = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel.value,
                       fade_type.value, colour, brightness]) + period.to_bytes(4, "big")
    return _add_padding(bytes)


def create_rgb_message(channel: CHANNEL, mode: FADE_TYPE, red, green, blue):
    bytes = bytearray([CTRL_CMD_ID.LED_CHANGE.value,
                       channel.value, mode.value, red, green, blue])
    return _add_padding(bytes)


def create_hsb_message(channel: CHANNEL, mode: FADE_TYPE, hue, saturation, brightness):
    hue_bytes = hue.to_bytes(2, "big")
    bytes = bytearray([CTRL_CMD_ID.LED_CHANGE.value, channel.value, mode.value]) + \
        hue_bytes + bytearray([saturation, brightness])
    return _add_padding(bytes)


def _add_padding(bytes):
    """_summary_: Adds padding to the message to ensure that the message is the correct size
    """
    padding_len = TX_MSG_SIZE - len(bytes)
    if padding_len > 0:
        bytes = bytes + bytearray([0] * padding_len)
    return bytes
