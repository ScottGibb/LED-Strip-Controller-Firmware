# LED Strip Controller Firmware

The LED Strip firmware is written using the Arduino framework. This allowed for a higher abstraction level achieved as well as STM32 clones to be used. A such a C++ Object orientated design was taken. Resulting in a set of Drivers and Handlers. The Resulting Firmware layers are shown below:

![Firmware Layers](../docs/Diagrams-Firmware%20Abstraction%20Layers.png)

As you can see in the above diagram, the system is built on a set of layers, each of which get more and more abstracted from the hardware. As you go up the stack, the concepts of pins and hardware specific functions becomes non existent.

# Class Diagram
As for the classes used in the design, the class diagram for the system is shown below:

![Class Diagram](../docs/Diagrams-Firmware%20Class%20Diagram.png)

There are many different types of classes in this design, which use structs as their configuration variables. Due to the complexity of the design, not all variables and methods are shown in the UML diagram. As well as this due to the nature of C++ code, not every file is a class. Files with methods that are not object orientated are highlighted in this diagram using a thick border. Examples of this are Firmware and CommsParser.

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
As for the Fade Driver, this is a special class which uses the colourDriver currently and a predefined method to create different patterns such as square, triangle and sine waves. This is all done inside the driver class. To add more to this simply add a new private method for the pattern and call it with the loop inside the class. Again these methods are designed to be polling and non-blocking methods

### HueDriver
Finally the last Driver to be discussed is the HueDriver, this is due to the need to have Hue control rather than RGB control. When integrating with Alexa, Node-Red uses Hue values rather than RGB. As such this functionality was built into the firmware using this converter class.

## FanController
Due to the ongoing switching and power regulation a fan was added to the design, As for controlling this fan it was decided that PWM control of the fan would be ideal so that it wasn't constantly on.

## CommsParser
The CommsParser file is responsible for decoding incoming messages and performing the corresponding actions. This means that this file is usually in control of the system as it responds to incoming requests from the user via a USB Serial channel. This file is not object orientated at present. It also contains a StateSaver Object which is used to store the most recent commands sent to the device.

## StateSaver
The StateSaver object is used to store the most recent commands sent to to the hardware, this is done so that they can be reloaded at the next boot sequence allowing the system to store its previous state. //todo Finish implementing this code

## PowerMonitor

One of the additional classes added to the firmware is the PowerMonitor class which is used to read voltage and current values from the PCB that the system sits on. It does this using current and voltage scalars so is independent on exact hardware, however these values are scaled using adc channels. So analogue sensors are required.

## StatusIndicator

Finally the last files to be discussed with this architecture is the StatusIndicator class. Which is a very simple class for simply flashing the on-board led, this is done to show the user that the system has not hung as the light will always flash if the main loop is running.

# Improvements
Many improvements to the firmware can be made, starting with the transitions to STM32 HAL based firmware. This would reduce the code size as well as allow more hardware features to be used such as removing the need for a polling based design and introducing a purely interrupt and timer driven architecture.

# Useful Links

- [STM32duino](https://github.com/stm32duino)