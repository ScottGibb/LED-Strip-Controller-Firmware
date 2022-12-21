# LED Strip Controller Firmware

The LED Strip firmware is written using the Arduino framework. This allowed for a higher abstraction level achieved as well as STM32 clones to be used. A such a C++ Object orientated design was taken. Resulting in a set of Drivers and Handlers. The Resulting Firmware layers are shown below:

![Firmware Layers](../docs/Diagrams-Firmware%20Abstraction%20Layers.png)

As you can see in the above diagram, the system is built on a set of layers, each of which get more and more abstracted from the hardware. As you go up the stack, the concepts of pins and hardware specific functions becomes non existent.

# Class Diagram
As for the classes used in the design, the class diagram for the system is shown below:

![Class Diagram](../docs/Diagrams-Firmware%20Class%20Diagram.png)

There are many different types of classes in this design, which use structs as their configuration variables. Due to the complexity of the design, not all variables and methods are shown in the UML diagram.

## ButtonsDriver

The ButtonsDriver class is responsible for running a software timed button system. This class constantly polls the pins fed into the object and will call the corresponding assigned function when a debounced button press happens. This was chosen over a interrupt based system, due to the ability of being able to place this object on any system regardless of wether the system had available interrupts.

## Button Handler

The Button Handler file is not a class but rather a collection of functions that can be pointed too by the ButtonsDriver.

## LEDDriver

At the lowest layer of abstraction there is an LEDDriver object which is responsible for sending the appropriate PWM signals to the physical hardware led. Due to the hardware using a RGD leds, this class effectively works as an RGB driver allowing the system to set individual colour intensities.

## Colour Drivers

At the next set of abstraction are a set of colour driving classes which do a variety of different functions. They all contain a reference to the the LEDDriver which is responsible for the PWM generation. This set of classes provided an extra level of abstraction for creating more complicated lighting effects.

### ColourDriver

The first driver for this was the ColourDriver class which is a very simple class that allow the user to select a colour from the COLOUR enum and the driver will then set the LEDs to this colour, the user can then set the brightness of this colour and the driver will work out how to do the rest.

### FadeDriver

### HueDriver

## FanController

## CommsParser

## Power Monitor

## StatusIndicator

# Improvements
Many improvements to the firmware can be made, starting with the transitions to STM32 HAL based firmware. This would reduce the code size as well as allow more hardware features to be used such as removing the need for a polling based design and introducing a purely interrupt and timer driven architecture.

# Useful Links

- [STM32duino](https://github.com/stm32duino)