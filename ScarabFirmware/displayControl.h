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
#include "pinFunctions.h"

#include <stdint.h>
#include <stdbool.h>

/// The display mode sets which LEDs are active
///
typedef enum
{
    DisplayLEDs_Off,      // Disable all LEDs
    DisplayLEDs_All,      // Enable all LEDs in circuit order 
    DisplayLEDs_ExtInt,   // Enable ext+int LEDs in visual order 
    DisplayLEDs_External, // Enable external LEDs in visual order
    DisplayLEDs_Internal, // Enable internal LEDs in visual order
    DisplayLEDs_Plates,   // Enable plates' LEDs in visual order
    DisplayLEDs_Menu      // Enable menu LEDs
} DisplayMode;


/// The state of the display
///
typedef enum {
    DisplayState_Init,      // Initial state
    DisplayState_Start,     // Starting display
    DisplayState_HeartFade, // Fade 'heart' LED under the cap-touch button
    DisplayState_Menu,      // Menu display
    DisplayState_Choices,   // Run display choice
} DisplayState;


/// 9 menu choices corresponding to 9 'external' LEDs, starting from to top
/// clock-wise viewed from the top side of the board
/// 
typedef enum
{
    DisplayChoice_Comet,         // Leading LED with a fading trail
    DisplayChoice_ExtScroll,     // External LEDs scrolling fast
    DisplayChoice_ExtScrollSlow, // External LEDs scrolling slow
    DisplayChoice_FadeInOut,     // All LEDs fading in and out
    DisplayChoice_AllDisco,      // All LEDs lighting up sequentially
    DisplayChoice_PlatesFade,    // LEDs on the two plates fading
    DisplayChoice_AllBlink,      // All LEDs blink
    DisplayChoice_AllFlicker,    // All LEDs flickering (sort of like a candle)
    DisplayChoice_LedTest        // What could this be?
} DisplayChoice;


/// Initialise the display module
///
void initDisplay();

/// Set a new display mode
///
void setDisplayMode(DisplayMode newMode);

/// Reset the display
///
void resetDisplay();

/// Set a new display state
///
void setDisplayState(DisplayState newState);

/// Get the current display mode
///
DisplayMode getDisplayMode();

/// Set a round limit
///
void setDisplayRoundLimit(uint16_t newLimit);

/// Return whether the amount of rounds have been exceeded
///
bool isDisplayDone();

/// Controls the display logic
///
void displayEventControl();


