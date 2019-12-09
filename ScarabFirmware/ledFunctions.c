// Part of the microcontroller firmware code for Boldport's 'Scarab'
// Copyright (C) 2019  Saar Drimer
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see https://www.gnu.org/licenses/.


#include "pinFunctions.h"
#include <compiler.h>

extern uint8_t gState;

void runExtIntLEDs()
{
    switch (gState)
    {
    case 0:     VPORTA.OUT |= 0b00000010;
                turnOffPB2();
                turnOnPB3();
                VPORTA.OUT ^= 0b00000100; break;
    case 1:     VPORTA.OUT ^= 0b00100100; break;
    case 2:     VPORTA.OUT ^= 0b00110000; break;
    case 3:     VPORTA.OUT ^= 0b00011000; break;
    case 4:     VPORTA.OUT ^= 0b00001000;
                turnOffPB3();
                turnOnPB1();
                VPORTA.OUT ^= 0b00100000; break;
    case 5:     VPORTA.OUT ^= 0b00101000; break;
    case 6:     VPORTA.OUT ^= 0b00001010; break;
    case 7:     VPORTA.OUT ^= 0b00000010;  
                turnOffPB1();
                turnOnPB2();
                VPORTA.OUT ^= 0b00100000; break;
    case 8:     VPORTA.OUT ^= 0b00110000; break;
    case 9:     VPORTA.OUT ^= 0b00011000; break;
    case 10:    VPORTA.OUT ^= 0b00001100; break;        
    case 11:    VPORTA.OUT ^= 0b00000100;
                turnOffPB2();
                turnOnPB3();
                VPORTA.OUT ^= 0b00000010; break;
    case 12:    VPORTA.OUT ^= 0b01000010; break;
    case 13:    VPORTA.OUT ^= 0b01000000; 
                turnOffPB3();
                turnOnPB1();
                VPORTA.OUT ^= 0b00010000; break;
    case 14:    VPORTA.OUT ^= 0b01010000; break;
    case 15:    turnOffPB1();
                turnOnPB2();              break;
    case 16:    VPORTA.OUT ^= 0b01000010; break;
    }
}

void runExternalLEDs()
{
    switch (gState)
    {
    case 0:     VPORTA.OUT |= 0b00000100;
                turnOffPB2();
                turnOnPB3();
                VPORTA.OUT ^= 0b00000100; break;
    case 1:     VPORTA.OUT ^= 0b00100100; break;
    case 2:     VPORTA.OUT ^= 0b00110000; break;
    case 3:     VPORTA.OUT ^= 0b00011000; break;
    case 4:     VPORTA.OUT ^= 0b00001000;
                turnOffPB3();
                turnOnPB1();
                VPORTA.OUT ^= 0b00100000; break;
    case 5:     VPORTA.OUT ^= 0b00101000; break;
    case 6:     VPORTA.OUT ^= 0b00001010; break;
    case 7:     VPORTA.OUT ^= 0b00000010;  
                turnOffPB1();
                turnOnPB2();
                VPORTA.OUT ^= 0b00100000; break;
    case 8:     VPORTA.OUT ^= 0b00110000; break;
    case 9:     VPORTA.OUT ^= 0b00011000; break;
    case 10:    VPORTA.OUT ^= 0b00001100; break;        
    }
}

void runInternalLEDs()
{
    switch (gState)
    {
    case 0:     turnOffPB2();
                turnOnPB3();
                VPORTA.OUT &= 0b01111101; break;
    case 1:     VPORTA.OUT ^= 0b01000010; break;
    case 2:     VPORTA.OUT ^= 0b01000000; 
                turnOffPB3();
                turnOnPB1();
                VPORTA.OUT ^= 0b00010000; break;
    case 3:     VPORTA.OUT ^= 0b01010000; break;
    case 4:     turnOffPB1();
                turnOnPB2();              break;
    case 5:     VPORTA.OUT ^= 0b01000010; break;
    }
}

void runAllLEDs()
{
    switch (gState)
    {
    case 0:     VPORTA.OUT |= 0b01000000;
                turnOffPB2();
                turnOnPB3();
                VPORTA.OUT ^= 0b00000010; break;
    case 1:     VPORTA.OUT ^= 0b00000110; break;
    case 2:     VPORTA.OUT ^= 0b00001100; break;
    case 3:     VPORTA.OUT ^= 0b00011000; break;
    case 4:     VPORTA.OUT ^= 0b00110000; break;
    case 5:     VPORTA.OUT ^= 0b01100000; break;
    case 6:     turnOffPB3();
                turnOnPB1();              break;
    case 7:     VPORTA.OUT ^= 0b01100000; break;
    case 8:     VPORTA.OUT ^= 0b00110000; break;
    case 9:     VPORTA.OUT ^= 0b00011000; break;
    case 10:    VPORTA.OUT ^= 0b00001100; break;
    case 11:    VPORTA.OUT ^= 0b00000110; break;
    case 12:    turnOffPB1();
                turnOnPB2();              break;
    case 13:    VPORTA.OUT ^= 0b00000110; break;
    case 14:    VPORTA.OUT ^= 0b00001100; break;
    case 15:    VPORTA.OUT ^= 0b00011000; break;
    case 16:    VPORTA.OUT ^= 0b00110000; break;          
    case 17:    VPORTA.OUT ^= 0b01100000; break;
    }
}

void runPlatesLEDs()
{
    switch (gState)
    {
    case 0:     VPORTA.OUT |= 0b00100000;
                turnOffPB2();
                turnOnPB3();
                VPORTA.OUT ^= 0b00000100; break;
    case 1:     VPORTA.OUT ^= 0b00100100; break;
    case 2:     VPORTA.OUT ^= 0b00110000; break;
    case 3:     VPORTA.OUT ^= 0b01010000; break;
    case 4:     VPORTA.OUT ^= 0b01000010; break;
    case 5:     turnOffPB3();
                turnOnPB1();              break;
    case 6:     VPORTA.OUT ^= 0b00000010;
                turnOffPB1();
                turnOnPB2();
                VPORTA.OUT ^= 0b00100000; break;
    }
}

void runMenuLEDs()
{
    switch (gState)
    {
    case 0:     VPORTA.OUT |= 0b00010000;
                turnOnPB3();
                VPORTA.OUT ^= 0b00100000; break;
    case 1:     VPORTA.OUT ^= 0b00100100; break;
    case 2:     turnOffPB3();
                turnOnPB2();              break;
    case 3:     VPORTA.OUT ^= 0b00001100; break;
    case 4:     VPORTA.OUT ^= 0b00011000; break;
    case 5:     VPORTA.OUT ^= 0b00010000;
                turnOffPB2();
                turnOnPB1();
                VPORTA.OUT ^= 0b00001000; break;
    case 6:     VPORTA.OUT ^= 0b00101000; break;
    case 7:     VPORTA.OUT ^= 0b00100000; 
                turnOffPB1();
                turnOnPB3();
                VPORTA.OUT ^= 0b00001000; break;
    case 8:     VPORTA.OUT ^= 0b00011000; break; 
    }
}


