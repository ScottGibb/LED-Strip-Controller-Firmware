# Node Red LED Strip Controller

# Summary
This repository contains all software,Firmware and Hardware for the LED Strip Controller. Which is a device used to control RGB Light Strips using an STM32 microcontroller and Node-Red. This allows for easy integration with Alexa whcih is my main controller for my Smart Home eco-system.

# STM32 HAL vs Arduino

Originally I wanted to develop the firmware using the STM32 HAL Drivers to allow for better control over the hardware of the STM32F1 series microcontroller. However it was found out that the microcontroller was actually a clone and thus could not be programmed using the STM32CubeIDE. Thus the easiest solution was to buy a new MCU which is not a clone. However this was not possible due to the on-going chip shortage of 2021-22. Thus the firmware had to be written in Arduino. However for all intensive purposes the desired functionality was still achieved.

# Design

The system developed in this repository is a true IOT Embedded System. Its purpose is to be as flexible as possible whilst maintaining an easy to Interface. This resulted in firmware and software. On The Microcontroller side, responsible for driving and controlling the LED Strips. There is a round robin firmware loop which is waiting to receive commands via UART over USB. This can be done through any means as long as its over a UART connection. In order to integrate with the rest of the Smart Home Eco System, Node-Red is used which is running in Docker on a Raspberry Pi. The Overall Architecture of the System is shown below:

![System Architecture](docs/Diagrams-System%20Diagram.png)

For Specific Details regarding the individual sections, please see the folders for firmware, Software and Hardware.

# Results

The LED Strip Controller was designed for the purpose of providing lights to my printer and CNC enclosure. The results of which are shown below:

![Printer Enclosure](docs/Server%20Rack%20Shelves%20Lights.jpg)

## Veroboard Version
Before moving on to a PCB design, the hardware was first created using Veroboard and an STM32 BluePill. The resulting Hardware along with the [3D printable case]() is shown below:

![Veroboard Design](docs/Veroboard%20Hardware.jpg)
![Veroboard Case](docs/Veroboad%20Case.png)

## PCB Version
After the Veroboard version was finalised, the resulting Hardware was designed using KiCad and the 3D Model and PCB are shown below:

![3D Model of PCB]()

![Populated PCB]()

# Required Software
 In order to Modify this project, the following software is recommended:
- [Kicad](https://www.kicad.org/)
- [Fusion 360](https://www.autodesk.com/products/fusion-360/overview)
- [Arduino IDE](https://www.arduino.cc/en/software)


# Useful Links
The following lists are useful websites that contain various information regarding the tools, hadware and software used in the project.
- [STM32 Blue Pill](https://www.aliexpress.com/item/1005003169244854.html?spm=a2g0o.productlist.0.0.7a7911b6BDtZsB&algo_pvid=5a7bc5c1-ddfc-4ccb-b4f4-ec7876c3e8b9&algo_exp_id=5a7bc5c1-ddfc-4ccb-b4f4-ec7876c3e8b9-1&pdp_ext_f=%7B%22sku_id%22%3A%2212000024471098729%22%7D&pdp_npi=2%40dis%21GBP%212.28%212.28%21%21%210.97%21%21%400b0a187b16647515460627480ec495%2112000024471098729%21sea&curPageLogUid=MVbSl8170TF7)
- [STM32 Programmer](https://www.aliexpress.com/item/1005003575620794.html?spm=a2g0o.productlist.0.0.7a7911b6BDtZsB&algo_pvid=5a7bc5c1-ddfc-4ccb-b4f4-ec7876c3e8b9&algo_exp_id=5a7bc5c1-ddfc-4ccb-b4f4-ec7876c3e8b9-16&pdp_ext_f=%7B%22sku_id%22%3A%2212000026345111930%22%7D&pdp_npi=2%40dis%21GBP%211.93%211.7%21%21%210.73%21%21%400b0a187b16647515460627480ec495%2112000026345111930%21sea&curPageLogUid=deXBnbPUx7W4)
- [Node-Red](https://nodered.org/)
- [Raspberry Pi 4](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)
- [Disco Mode LED Shelves Video]()
- [Veroboard 3D Printable Case]()
- [PCB 3D Printable Case]()
- [LED Strips](https://www.aliexpress.com/item/1005004256916343.html?spm=a2g0o.productlist.0.0.77cb6e98v91KTK&algo_pvid=8fc57f13-675e-445c-abd6-b97ed1278c4b&algo_exp_id=8fc57f13-675e-445c-abd6-b97ed1278c4b-2&pdp_ext_f=%7B%22sku_id%22%3A%2212000028543714961%22%7D&pdp_npi=2%40dis%21GBP%215.47%214.43%21%21%21%21%21%400b0a0ae216647517007916760e599b%2112000028543714961%21sea&curPageLogUid=9ESjOjFpbzUi)
