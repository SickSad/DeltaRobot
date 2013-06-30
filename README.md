DeltaRobot
==========

Introduction
------------

This repository contains the mechnical design, firmware and software to build and control a delta robot.

This project is very much a work in progress, the final intention is for it to be a 3D printer. But many diversions along the way have shaped it's developement.

The electronics are based around an stm32f4 Discovery development board, while the mechanical and software are both custom built.

Project Structure
-----------------
The project is loosely structred as follows:

    /desgin - The mechnical design
    /firmware - The firmware running on the stm32f4 discovery board
    /python - Computer side control software


Electronics
-----------
Unfortunately the electronics for this project are largely undocumented. Some of the connections can be infered from the file "/firmware/hardware.h" which details how the stm32f4 discovery board is connected to Pololu AD4988 stepper motor cards.
It is not recommended to attempt building this if you have no electronics experince. But it should be pretty straight forward for anyone capable of weilding a soldering iron and drawing schematics.

License
-------
This project is under a Creative Commons Attribution-ShareAlike 3.0 Unported license, some files are based on work from the libopencm3 project and have relevant licenses in the files.

More details can be found here:
[http://creativecommons.org/licenses/by-sa/3.0/](http://creativecommons.org/licenses/by-sa/3.0/)

