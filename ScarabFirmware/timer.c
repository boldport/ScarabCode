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


#include "timer.h"

#include "displayControl.h"

#include <interrupt_avr8.h>


volatile uint32_t gTimer = 0;

uint32_t getCurrentTime(void) {
    return gTimer;
}

// Event timer
ISR (TCB0_INT_vect) {
    gTimer += 1;
    TCB0.INTFLAGS = TCB_CAPT_bm; // Clear interrupt flag
}
