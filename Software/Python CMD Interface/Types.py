from enum import Enum


class COLOUR(Enum):
    RED = 0
    GREEN = 1
    BLUE = 2
    WHITE = 3
    ROSE = 4
    MAGENTA = 5
    VIOLET = 6
    AZURE = 7
    CYAN = 8
    AQUAMARINE = 9
    CHARTREUSE = 10
    YELLOW = 11
    ORANGE = 12


class FADE_TYPE(Enum):
    NONE = 0
    SINE = 1
    SQUARE = 2
    TRIANGLE = 3
    SAWTOOTH = 4
    COLOUR_CHANGE = 5
    RGB_CTRL = 6
    HUE_CTRL = 7


class CHANNEL(Enum):
    CHANNEL_NS = 0
    CHANNEL_1 = 1
    CHANNEL_2 = 2
    CHANNEL_3 = 3
