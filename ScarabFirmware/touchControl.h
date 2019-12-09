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


#pragma once

#include "eventControl.h"
#include "touch.h"

#include "stdint.h"
#include "stdbool.h"

/// Names for touch lengths
typedef enum {
    NoTouch,
    ShortTouch,
    MidTouch,
    LongTouch,
    VLongTouch
} TouchName;

/// Returns the length name of the last touch captured
TouchName getLastTouch();

/// Initialise the touch interface
void initTouch();