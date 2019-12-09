Microcontroller firmware for Boldport's Scarab
==============================================

This code is for use with the Scarab project created by Boldport.

The target is Microchip's ATtiny1614. The assumed development environment is MPLAB-X v5.30 or greater with the XC8 compiler. 

Programming
-----------

The ATtiny1614 programing interface is UPDI, so you'd need a UPDI programmer and connect `[power, ground, UPDI]` wires to the PCB to get the hex onto the chip.

License
-------

This software is distributed under GPL 3; see LICENSE. 

Thanks
------

Many thanks to [LuckResistor](https://luckyresistor.me) for helping with the architecture of the code and suggesting better ways to implement the functionality in a clean and modular way.
