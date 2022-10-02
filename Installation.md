# LED Strip Controller Installation

The LED Strip Controller Software installation comes in two sections, the Arduino code running in the STM32 Hardware and the Node-Red flow running on the Node-Red docker container. The installation process for each is shown below:

# STM32 PCB Arduino Install

Assuming you bough the hardware designed in the repository and it is manufactured. To install the firware you will also need an STM32 Debugger and the Arduino IDE installed. Once those are installed/bought, install the STM32duino boards package to arduino ide and then use the following settings to program the STM32 on the board. Once done the status LED on the board should start flashing.

![Programmer Settings]()

# Node Red Install

As for the Node-Red install, launch your exisiting Node-Red and import the flow file found in the Software folder. Plug in the STM32 hardware and set the apropriate serial port and test using the inject buttons to see if the hardware will light up.