# Node Red LED Strip Controller

# Summary
This repository contains all software,Firmware and Hardware for the LED Strip Controller. Which is a device used to control RGB Light Strips using an STM32 microcontroller and Node-Red. This allows for easy integration with Alexa whcih is my main controller for my Smart Home eco-system.

# STM32 HAL vs Arduino

Originally I wanted to develop the firmware using the STM32 HAL Drivers to allow for better control over the hardware of the STM32F1 series microcontroller. However it was found out that the microcontroller was actually a clone and thus could not be programmed using the STM32CubeIDE. Thus the easiest solution was to buy a new MCU which is not a clone. However this was not possible due to the on-going chip shortage of 2021-22. Thus the firmware had to be written in Arduino. However for all intensive purposes the desired functionality was still achieved.

# Design

The system developed in this repository is a true IOT Embedded System. Its purpose is to be as flexible as possible whilst maintaining an easy to Interface. This resulted in firmware and software. On The Microcontroller side, responsible for driving and controlling the LED Strips. There is a round robin firmware loop which is waiting to receive commands via UART over USB. This can be done through any means as long as its over a UART connection. In order to integrate with the rest of the Smart Home Eco System, Node-Red is used which is running in Docker on a Raspberry Pi. The Overall Architecture of the System is shown below:

![System Architecture]()

For Specific Details regarding the individual sections, please see the folders for firmware, Software and Hardware.

# Results

## Veroboard Version
Before moving on to a PCB design, the hardware was first created using Veroboard and an STM32 BluePill. The resulting Hardware along with the [3D printable case]() is shown below:

![Veroboard Design]()

## PCB Version
After the Veroboard version was finalised, the resulting Hardware was designed and the 3D Model and PCB are shown below:

![3D Model of PCB]()

![Populated PCB]()

# Required Software
 In order to Modify this project, the following software is recommended:
-[Kicad]()
-[Fusion 360]()
-[Arduino IDE]()


# Useful Links
The following lists are useful websites that contain various information regarding the tools, hadware and software used in the project.
- [STM32 Blue Pill]()
- [STM32 Programmer]()
- [STM32duino]()
- [Node-Red]()
- [Raspberry Pi 4]()
