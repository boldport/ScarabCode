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

extern bool gPwmEnabled;

void turnOffPB1()
{    
    if (gPwmEnabled == true)
        TCA0.SINGLE.CTRLB &= ~(1 << TCA_SINGLE_CMP1EN_bp);
    else
        VPORTB.OUT &= ~(1 << 1);
}

void turnOnPB1()
{    
    if (gPwmEnabled == true)
        TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP1EN_bp);
    else
        VPORTB.OUT |= (1 << 1);
}

void turnOffPB2()
{    
    if (gPwmEnabled == true)
        TCA0.SINGLE.CTRLB &= ~(1 << TCA_SINGLE_CMP2EN_bp);
    else
        VPORTB.OUT &= ~(1 << 2);
}

void turnOnPB2()
{
    if (gPwmEnabled == true)
        TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP2EN_bp);
    else
        VPORTB.OUT |= (1 << 2);
}

void turnOffPB3()
{    
    if (gPwmEnabled == true)
        TCA0.SINGLE.CTRLB &= ~(1 << TCA_SINGLE_CMP0EN_bp);
    else
        VPORTB.OUT &= ~(1 << 3);
}

void turnOnPB3()
{    
    if (gPwmEnabled == true)
        TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP0EN_bp);
    else
        VPORTB.OUT |= (1 << 3);
}
