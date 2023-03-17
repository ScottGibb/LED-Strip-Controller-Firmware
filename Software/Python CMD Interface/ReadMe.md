# Python Command Line Interface

## Summary

The Python command Line interface is a very simple python interface which uses the pyserial package to create serial packets over USB. Due to the nature of the device in that the system works as a generic USB, It was decided that Python and Docker would be used to launch the software on systems. As this allows the command line interface to be used on any operating system wether it has a graphical user interface like windows or a server based system like Linux.

## Docker
As for Docker, the Dockerfile is held in this repository and can be created using the bash script run.sh. This does all the building of the image and the running of the container. At the moment the system runs in privileged mode which is not-ideal, however for the purpose of this software which is for debugging the hardware and ensuring that its running correctly, this should not matter much.

![System Design Diagram](../../docs/Diagrams-Python%20Docker%20System%20Design.png)

## Installation Instructions
As for the installation of this program, the steps are listed below:

- Download Repository
- navigate to current directory
- run the run.sh script
- Attach to the running container
- Follow the command interface Instructions

## Improvements
As for improvements to the python command interface, the following changes could be made:

- Run Docker container in normal mode, not privileged mode
- Add Exception handling for malformed user input
- Add option to change serial com port

# Useful Links

- [Docker](https://docs.docker.com/)
- [Portainer](https://www.portainer.io/)
- [Python](https://www.python.org/)
- [PySerial](https://pyserial.readthedocs.io/en/latest/)