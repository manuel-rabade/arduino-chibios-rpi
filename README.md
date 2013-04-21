arduino-chibios-rpi
===================

This project solves an Ardusat challenge from the International Space Apps Challenge (http://2013.spaceappschallenge.org/challenge/ardusat/).

It addresses the hardware level 3 challenge by using a Raspberry Pi running ChibiOS (a Real Time Operating System for embedded systems). Inside the RTOS lives threads that runs code with help of a library that tries to mimic the Arduino platform.Via software can be configured the mapping for pins and devices betwen the Raspberry Pi and the virtual Arduinos allowing the use of all sensors in an Ardustat anytime. The code and configuration running on the Raspberry pi can be uploaded via serial console for remote management.

This is a just proof of concept that multiple threads inside a RTOS can "emulate" an Arduino and it's not intended to be a full working prototype. The example pin configuration is:

Raspberry Pi    Arduino #
GPIO17          arduino0 pin 13
GPIO22          arduino1 pin 13
GPIO24          arduino2 pin 13
GPIO25          arduino3 pin 13
