Arduinos on the Raspberry Pi
============================

    git clone https://github.com/steve-bate/ChibiOS-RPi

#### Get Arduinos on the Raspbery Pi

    git clone https://github.com/manuel-rabade/arduino-chibios-rpi

#### Build

    cd arduino-chibios-rpi && make
    cd arduino-chibios-rpi/bootloader && make

#### Setup SD card

Copy arduino-chibios-rpi/bootloader/kernel.img to the SD card. Download [bootcode.bin and start.elf](https://github.com/raspberrypi/firmware) and copy them to the SD card.

#### Serial console

Install minicom and configure it:

    Serial Device : /dev/ttyUSB0 
    Bps/Par/Bits : 115200 8N1
    Hardware Flow Control : No
    Software Flow Control : No

#### Boot

Power your Raspberry Pi and upload arduino-chibios-rpi/build/ch.bin using XModem.

## Serial console

Once ChibiOS has been uploaded the following commands are available in the serial shell:

* status: get virtual Arduinos status
* pause [arduino #]: pause operation of a virtual Arduino
* resume [arduino #]: resume operation of a virtual Arduino
* log [arduino #]: get the serial buffer of a virtual Arduino
* mem: get ChibiOS memory usage
* threads: get ChibiOS threads status
* info: get ChibiOS build information
* systime: get system time
* reboot: reboot ChibiOS

## Pin configuration

This project map the following Raspberry Pi pins to virtual Arduino pins:

    Raspberry Pi    Virtual Arduino   Arduino pin
    GPIO22          arduino0          13
    GPIO7           arduino1          13
    GPIO25          arduino1          12
    GPIO17          arduino2          13
    GPIO24          arduino3          13

## Hack

arduino-chibios-rpi/main.cpp it's the entry point that spawns the threads.

arduino-chibios-rpi/arduino/arduino0.cpp, arduino-chibios-rpi/arduino/arduino1.cpp, arduino-chibios-rpi/arduino/arduino2.cpp and arduino-chibios-rpi/arduino/arduino3.cpp are the code for each virtual Arduino.

arduino-chibios-rpi/arduino-chibios-rpi/arduino/arduino0.h, arduino-chibios-rpi/arduino/arduino1.h, arduino-chibios-rpi/arduino/arduino2.h and arduino-chibios-rpi/arduino/arduino3.h are the configuration for each Arduino.

arduino-chibios-rpi/arduino/arduino.h and arduino-chibios-rpi/arduino/arduino.cpp is the library that "emulates" the Arduino plataform.

## References

* [Ardusat challenges](http://2013.spaceappschallenge.org/challenge/ardusat/)
* [ChibiOS-RPi port and demos by Steve Bate](https://github.com/steve-bate/ChibiOS-RPi)
* [Raspberry Pi bootloader by David Welch](https://github.com/dwelch67/raspberrypi/tree/master/bootloader05)
* [Arduino languaje reference and source code](http://arduino.cc/en/Reference/HomePage)
* [Raspberry Pi Low-level peripherals](http://elinux.org/RPi_Low-level_peripherals)
