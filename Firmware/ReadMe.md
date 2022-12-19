# LED Strip Controller Firmware

The LED Strip firmware is written using the Arduino framework. This allowed for a higher abstraction level achieved as well as STM32 clones to be used. A such a C++ Object orientated design was taken. Resulting in a set of Drivers and Handlers. The Resulting Firmware layers are shown below:

![Firmware Layers]()

# Class Diagram
As for the classes used in the design, the class diagram for the system is shown below:

![Class Diagram]()


## ButtonsDriver

## Button Handler

## LEDDriver

## ColourDriver

## FadeDriver

## HueDriver

## FanController

## CommsParser

## Power Monitor

## StatusIndicator

# Improvements
Many improvements to the firmware can be made, starting with the transitions to STM32 HAL based firmware. This would reduce the code size as well as allow more hardware features to be used such as removing the need for a polling based design and introducing a purely interrupt and timer driven architecture.

# Useful Links

- [STM32duino](https://github.com/stm32duino)