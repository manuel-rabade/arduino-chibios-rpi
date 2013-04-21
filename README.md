arduino-chibios-rpi
===================

This project solves an Ardusat challenge from the International Space Apps Challenge (http://2013.spaceappschallenge.org/challenge/ardusat/).

It addresses the hardware level 3 challenge by using a Raspberry Pi running ChibiOS (a Real Time Operating System for embedded systems). Inside the RTOS lives threads that runs code with help of a library that tries to mimic the Arduino platform.Via software can be configured the mapping for pins and devices betwen the Raspberry Pi and the virtual Arduinos allowing the use of all sensors in an Ardustat anytime. The code and configuration running on the Raspberry pi can be uploaded via serial console for remote management.

This is a just proof of concept that multiple threads inside a RTOS can "emulate" an Arduino and it's not intended to be a full working prototype.

The example pin configuration is:

    Raspberry Pi    Arduino #
    GPIO17          arduino0 pin 13
    GPIO22          arduino1 pin 13
    GPIO24          arduino2 pin 13
    GPIO25          arduino3 pin 13
    GPIO7           arduino3 pin 12

To build & run (for OS X, Linux is only at home sorry):

1. Install yagarto: http://www.yagarto.de/#downloadmac
2. Clone ChibiOS for the RPi: git clone https://github.com/steve-bate/ChibiOS-RPi
3. Download bootcode.bin and start.elf in the sd card: https://github.com/raspberrypi/firmware
4. Build this example: 
    git clone https://github.com/manuel-rabade/arduino-chibios-rpi
    cd arduino-chibios-rpi && make
5. Copy build/ch.bin to the sd card under the name kernel.img

To hack:

1. Review main.cpp, it's the program entry point that spawns the threads
2. Code for each arduino is in arduino0.cpp, arduino1.cpp, arduino2.cpp and arduino3.cpp
3. Configuration for each arduino is in arduino0.h, arduino1.h, arduino2.h and arduino3.h
4. The arduino.h and arduino.cpp is the library that mimics the Arduino plataform.

This example is based on the ChibiOS-RPi demos by Steve Bate (https://github.com/steve-bate/ChibiOS-RPi)
