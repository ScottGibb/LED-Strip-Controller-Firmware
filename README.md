# LED Strip Controller Firmware

<center>
<img src="docs/Languages-And-Tools.png">
</center>

## Summary

This repository contains all the firmware to control the LED Strip Controller Hardware variations. The firmware is written in C++ using the Arduino framework, originally I wanted to use the STM32 HAL Drivers, however, the STM32 Microcontrollers were cloned and this resulted in the Arduino framework being used. The firmware is designed to be as flexible as possible, whilst maintaining an easy-to-use interface. The firmware is designed to be used with the LED Strip Controller Software Applications that are described below. The firmware is designed to be used with different microcontrollers.

## System Architecture

As for the system architecture it's designed to be interacted with via a byte stream sent over an interface. At present there is a UART interface over USB. However, there are plans to utilize an IP interface over WiFi. The byte stream is then parsed by the firmware and the appropriate action is taken. The firmware is designed to be as flexible as possible, whilst maintaining an easy-to-use interface. The firmware is designed to be used with the LED Strip Controller Software Applications. The architecture of the full system, it is shown below:

<center>

![System Architecture](docs/High_Level_System_Diagram.png)

</center>

## Firmware Design

The firmware is designed to utilize modern C++ principles and be fully object orientated. This was done to allow me to utilize the full power of the C++ language and also allow me to learn new features regarding the language. The class diagram for the firmware is shown below:

<center>
<img src = "docs/Diagrams-Firmware Class Diagram.png">
</center>

The firmware is split into multiple layers which follow this layer convention:

<center>
<img src = "docs/Diagrams-Firmware Abstraction Layers.png">
</center>

The idea behind this is that the Arduino layer is abstracted away from the rest of the firmware. This allows the firmware logic to be used across multiple platforms and prevents it from being tied into the Arduino framework.


## Memory Map

The system does require some onboard memory to utilize the User Mode system. This allows the user to create custom colour waveforms and thus create custom effects. The memory map for the STM32F103C8T6 microcontroller is shown below:

<center>
<img src = "docs/Memory Map.png">
</center>


## LED Strip Controller Repository Links

- [Manifest](https://github.com/ScottGibb/LED-Strip-Controller-Manifest) This repository contains the manifest file for the LED Strip Controller project. Which allows the cloning of all the repositories in one go.
- [Hardware](https://github.com/ScottGibb/LED-Strip-Controller-Hardware) This repository contains the hardware design files for the LED Strip Controller project.
- [Firmware](https://github.com/ScottGibb/LED-Strip-Controller-Firmware) This repository contains the firmware for the LED Strip Controller project.
- [Software](https://github.com/ScottGibb/LED-Strip-Controller-Software) This repository contains the software for the LED Strip Controller project.

