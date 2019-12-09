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


#include "mainControl.h"

#include "eventControl.h"
#include "touchControl.h"
#include "displayControl.h"

#include <stdint.h>


typedef enum {
    Start,
    HeartFade,
    Menu,
    Choices
} StateName;

StateName gStateName = Start;
DisplayChoice gMenuChoice = DisplayChoice_Comet;
ChoiceAction gChoiceAction = ChoiceModeAction_None;

/// Fade in and out at startup;
/// runs until the initial value of gRunLimit is reached
void runStateStart()
{
    if (isDisplayDone())
        gStateName = HeartFade;
}

/// 'Heart' LED fading in and out while waiting for a touch event
///
void runHeartFade()
{
    setDisplayState(DisplayState_HeartFade);
    const TouchName lastTouch = getLastTouch();

    switch (lastTouch)
    {
    case MidTouch: gStateName = Menu; break;
    default: break;
    }
}

/// The menu scrolls through external LEDs each representing a 'Choice'
/// The menu option persists between leaving and entering the menu
void runMenu()
{    
    setDisplayState(DisplayState_Menu);
    const TouchName lastTouch = getLastTouch();

    switch (lastTouch)
    {
    case ShortTouch:
        if (gMenuChoice < 8u)
            gMenuChoice += 1u;
        else
            gMenuChoice = DisplayChoice_Comet;
        break;
    case MidTouch:
        gStateName = Choices;
        break;
    case VLongTouch:
        gStateName = Start;
        break;
    default: break;
    }
}

/// Once a choice has been made the display state changes to show
/// the appropriate display
void runChoices()
{
    setDisplayState(DisplayState_Choices);
    const TouchName lastTouch = getLastTouch();
    
    switch (lastTouch)
    {
    case ShortTouch: gChoiceAction = ChoiceModeAction_One; break;
    case MidTouch:   gChoiceAction = ChoiceModeAction_Two; break;
    case LongTouch:  gStateName = HeartFade;               break;
    case VLongTouch: gStateName = Start;                   break;
    default: break;
    }   
}


/// The main control state machine
///
void mainControl()
{
    switch(gStateName)
    {
    case Start:     runStateStart(); break;
    case HeartFade: runHeartFade();  break;
    case Menu:      runMenu();       break;
    case Choices:   runChoices();    break;
    }
}


void clearChoiceAction()
{
    gChoiceAction = ChoiceModeAction_None;
}

/// Register the control state machine to the event system
///
void initMainControl()
{
    const uint8_t tickInterval = 10u;
    registerEvent(&mainControl, tickInterval);
}
