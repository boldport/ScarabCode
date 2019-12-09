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


#include "touchControl.h"

/// Located in pre-compiled QTouch blobs
///
extern volatile uint8_t measurement_done_touch;

/// The number of predefined touch lengths.
///
const uint8_t cTouchLengthsSize = 4;

/// Touch lengths in Touch event ticks
///
const uint16_t cTouchLengths[] = {8, 75, 250, 800};

bool gTouchActive = false;

/// The last touch length of the pad.
///
TouchName gTouch;

/// The last state if the pad was touched.
///
bool gLastTouchActive = false;


/// Set the touch length, based on the counter.
///
void setTouchLength(uint16_t count)
{
    TouchName newTouch = VLongTouch;
    for (uint8_t i=0 ; i<cTouchLengthsSize ; ++i)
    {
        if (count < cTouchLengths[i])
        {
            newTouch = (TouchName)(i);
            break;
        }
    }
    gTouch = newTouch;
}

/// Detect touches to the pad
///
void detectTouch()
{
    static uint16_t count = 0;
    
    touch_process(); // From QTouch library

    if (measurement_done_touch == 1)
    {
        bool touchIsActive = ((get_sensor_state(0) & KEY_TOUCHED_MASK) != 0);
        
        if (touchIsActive != gLastTouchActive)
        {
            gLastTouchActive = touchIsActive;
            if (!touchIsActive)
            {
                setTouchLength(count);
                count = 0;
            }        
        }
        if (touchIsActive)
        {
            count += 1;
        }
    }
}

TouchName getLastTouch()
{
    const TouchName result = gTouch;
    gTouch = NoTouch; // Clear
    return result;
}


void initTouch()
{
    const uint8_t tickInterval = 10u;
    registerEvent(&detectTouch, tickInterval);
}
