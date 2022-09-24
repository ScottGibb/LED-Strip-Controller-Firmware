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
    SINE = 0
    SQUARE = 1
    TRIANGLE = 2
    SAWTOOTH = 3
    NONE = 4


class CHANNEL(Enum):
    CHANNEL_NS = 0
    CHANNEL_1 = 1
    CHANNEL_2 = 2
    CHANNEL_3 = 3
