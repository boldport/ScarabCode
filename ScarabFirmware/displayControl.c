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


#include "displayControl.h"
#include "touchControl.h"
#include "mainControl.h"

#include "pwmControl.h"
#include "ledFunctions.h"
#include "tcb.h"

#include <stdint.h>
#include <stdbool.h>


uint8_t gState = 0;
uint8_t gModeStateCount;
uint16_t gRoundCount = 0;
uint16_t gSpeedCountLimit = 0;

/// This is the amount of cycles through the display mode before the done
/// flag is raised.
/// The length of the initial fade in and out is conrolled by the initial 
/// value set here
///
uint16_t gRoundLimit = 1850;

/// The current display mode
///
DisplayMode gMode = DisplayLEDs_All;

/// The current state of the display.
///
DisplayState gDisplayState = DisplayState_Init;

/// The current selected animation.
///
DisplayChoice gDisplayChoice = DisplayChoice_Comet;

extern bool gPwmEnabled;
extern DisplayChoice gMenuChoice;
extern ChoiceAction gChoiceAction;

/// Display timer
///
ISR (TCB1_INT_vect) {
    
    static uint16_t count = 0;
    
    if (count == gSpeedCountLimit)
    {
        displayEventControl();
        count = 0;
    } else {
        count += 1; 
    }
        
    TCB1.INTFLAGS = TCB_CAPT_bm; // Clear interrupt flag
}


/// Returns the appropriate amount of states for the current display mode
///
uint8_t getModeStateCount()
{
    uint8_t count = 0;
    switch (gMode)
    {
    case DisplayLEDs_Off:      count = 0;  break; 
    case DisplayLEDs_All:      count = 17; break;
    case DisplayLEDs_ExtInt:   count = 16; break;
    case DisplayLEDs_External: count = 10; break;
    case DisplayLEDs_Internal: count = 5;  break;
    case DisplayLEDs_Plates:   count = 6;  break;
    case DisplayLEDs_Menu:     count = 8;  break;
    }
    return count;
}


void resetState()
{
    gState = 0;
    gRoundCount = 0;
    gModeStateCount = getModeStateCount();
}


void resetDisplay()
{
    VPORTA.OUT |= 0b01111110;
    turnOffPB1();
    turnOffPB2();
    turnOffPB3();
    resetState();
}


void setDisplayMode(DisplayMode newMode)
{
    gMode = newMode;
    resetState();
    resetDisplay();
}


DisplayMode getDisplayMode()
{
    return gMode;
}


void setDisplayRoundLimit(uint16_t newLimit)
{
    gRoundLimit = newLimit;
}


bool isDisplayDone()
{
    bool result = (gRoundCount >= gRoundLimit);
    return result;
}


/// Advance the display to the next state
///
void advDisplay()
{    
    switch (gMode) 
    {
    case DisplayLEDs_Off:                         break;
    case DisplayLEDs_All:      runAllLEDs();      break;
    case DisplayLEDs_ExtInt:   runExtIntLEDs();   break;
    case DisplayLEDs_External: runExternalLEDs(); break;
    case DisplayLEDs_Internal: runInternalLEDs(); break;          
    case DisplayLEDs_Plates:   runPlatesLEDs();   break;
    case DisplayLEDs_Menu:     runMenuLEDs();     break;
    }

    if (gState < gModeStateCount) 
    {
        gState += 1;
    }
    else
    {
        gState = 0;
        gRoundCount += 1;
    }
}


// Runs at the start
// 
void displayStartSwitch(void)
{
    enablePwm();
    setDisplayMode(DisplayLEDs_All);
}


void displayStart(void)
{
    advDisplay();
}


// HeartFade
// 
void displayHeartFadeSwitch(void)
{
    enablePwm();
    resetState();
    resetDisplay();
    turnOnPB1();
    turnOffPB2();
    turnOffPB3();
    VPORTA.OUT = 0b01111010;
}

void displayHeartFade()
{
}

// Menu
// 
void displayMenuSwitch(void)
{
    disablePwm();
    setDisplayMode(DisplayLEDs_Menu);
    for (uint8_t i=0 ; i<=(int)gMenuChoice ; i++)
    {
        advDisplay();
    }
}

void displayMenu(void)
{
    static DisplayChoice currentChoice = DisplayChoice_Comet;
    
    if (currentChoice != gMenuChoice)
    {
        currentChoice = gMenuChoice;
        advDisplay();
    }
}


void setDisplaySpeed(uint16_t newCountLimit)
{
    gSpeedCountLimit = newCountLimit;
}

// Choices
// 
void displayChoicesSwitch(void)
{
    gDisplayChoice = (DisplayChoice)gMenuChoice;
    
    switch (gDisplayChoice) 
    {
    case DisplayChoice_Comet:
        disablePwm();   
        setDisplayMode(DisplayLEDs_External);
        setDisplaySpeed(1000u);
        break;
    case DisplayChoice_ExtScroll:
        disablePwm();           
        setDisplayMode(DisplayLEDs_External);
        setDisplaySpeed(300u);
        break;
    case DisplayChoice_ExtScrollSlow:
        disablePwm();
        setDisplayMode(DisplayLEDs_External);
        setDisplaySpeed(1500u);
        break;
    case DisplayChoice_FadeInOut:
        enablePwm();
        setEventInterval(&updatePwm, 30u);
        setDisplayMode(DisplayLEDs_External);
        resetPwmRounds();
        setDisplaySpeed(1u);
        break;
    case DisplayChoice_AllDisco:
        disablePwm();
        setDisplaySpeed(200u);
        setDisplayMode(DisplayLEDs_All);
        break;
    case DisplayChoice_PlatesFade:
        enablePwm();
        setEventInterval(&updatePwm, 10u);
        setDisplayMode(DisplayLEDs_Plates);
        setDisplaySpeed(1u);
        break;
    case DisplayChoice_AllBlink:
        disablePwm();
        setDisplaySpeed(1u);
        setDisplayMode(DisplayLEDs_All);
        break;
    case DisplayChoice_AllFlicker:
        disablePwm();
        setDisplaySpeed(1u);
        setDisplayMode(DisplayLEDs_All);
        break;
    case DisplayChoice_LedTest:
        setDisplayMode(DisplayLEDs_All);
        break;
    }
}


void displayChoices()
{
    advDisplay();
}

/// A leading LED with a two trailing LEDs at lower brightness
///
void displayChoiceComet()
{   
    static uint8_t LED1 = 2u;
    static uint8_t LED2 = 1u;
    static uint8_t LED3 = 0;
    
    static uint8_t ledCount = 0u;
    static uint16_t speedCount = 0u;
    
    if (ledCount == LED1)
    {
        setDisplaySpeed(20u);
    }    
    else if (ledCount == LED2)
    {    
        setDisplaySpeed(10u);
    }    
    else if (ledCount == LED3)
    {
        setDisplaySpeed(3u);
    }
    else
    {   
        setDisplaySpeed(0u);
    }    
    
    if (ledCount < 10u)
    {
        ledCount += 1u;
    }
    else
    {
        ledCount = 0;
    }
    
    if (speedCount == 100u)
    {
        switch (LED3)
        {
        case 8:
            LED1 = 0;
            LED2 = 10u;
            LED3 = 9u;
            break;
        case 9:
            LED1 = 1u;
            LED2 = 0;
            LED3 = 10u;
            break;
        case 10:
            LED1 = 2u;
            LED2 = 1u;
            LED3 = 0;
            break;
        default:
            LED1 += 1u;
            LED2 += 1u;
            LED3 += 1u;
            break;
        }
        speedCount = 0;
    }
    else
    {
        speedCount += 1u;
    }
    
    advDisplay();
}


/// External LED scroll with varying speeds
///
void displayChoiceExtScroll()
{   
    static bool switchBetween = false;
    static uint16_t count = 300u;
    static int8_t sign = 1;
    uint8_t inc = 5u; // Keep in multiples of 5 for the ExtInt to kick in

    if (count > 750u)
    {
        sign = -1;
    }

    // Add internal LEDs when it's scrolling faster.
    // This kicks in on the way up and the way down
    if (count == 280u)
    {
        setDisplayMode(switchBetween ? DisplayLEDs_External : DisplayLEDs_ExtInt);
        switchBetween = !switchBetween;
    }

    if (count <= 10u)
    {
        sign = 1;
    }

    count += (inc*sign);
    setDisplaySpeed(count);    
    advDisplay();
}


/// Slow scroll of external LED with an internal LED 'accent' every
/// 6 cycles
///
void displayChoiceExtScrollSlow()
{   
    static uint8_t count = 0;
    
    static bool internalLeds = false;
    
//    if (count == 66u)
//    {
//        setDisplayMode(DisplayLEDs_ExtInt);
//    }
//    
//    if (count == 83u)
//    {
//        setDisplayMode(DisplayLEDs_External);
//        count = 0;
//    }

    switch (gChoiceAction)
    {
    case ChoiceModeAction_None:
        break;
    case ChoiceModeAction_One:
        setDisplayMode(DisplayLEDs_Internal);
        internalLeds = true;
        clearChoiceAction();
        break;
    case ChoiceModeAction_Two:
        break;
    }        

    if (internalLeds == true)
        count += 1;
    else
        count = 0;
    
    if (count == 14)
    {
        setDisplayMode(DisplayLEDs_External);
        internalLeds = false;
    }
    
    advDisplay();
}


/// Fade external LEDs in and out and every certain amount of cycles
/// switch to internal LED fade
///
void displayChoiceFadeInOut()
{   

    static bool inInternalMode = false;
    static uint8_t tickInterval = 30u;
    
    if ((getPwmRounds() == 9) && (inInternalMode == false)) {
        setDisplayMode(DisplayLEDs_Internal);
        inInternalMode = true;
    }

    if (getPwmRounds() == 10)
    {
        setDisplayMode(DisplayLEDs_External);
        resetPwmRounds();
        inInternalMode = false;
    }

    // Short press causes faster fade, mid-press slower
    switch (gChoiceAction)
    {
    case ChoiceModeAction_None:
        break;
    case ChoiceModeAction_One:
        clearChoiceAction();
        if (tickInterval > 3);
        tickInterval -= 2u;
        setEventInterval(&updatePwm, tickInterval);   
        break;
    case ChoiceModeAction_Two:
        clearChoiceAction();
        if (tickInterval < 200)
            tickInterval += 2u;
        setEventInterval(&updatePwm, tickInterval);   
        break;
    }
    
    advDisplay();
}


/// Blink all LEDs by switching between two display modes
///
void displayChoiceAllBlink()
{   
    static bool switchBetween = false;
    static uint16_t count = 0;
    
    if (count == 2000u)
    {
        setDisplayMode(switchBetween ? DisplayLEDs_Off : DisplayLEDs_All);
        switchBetween = !switchBetween;
        count = 0;
    }
    else
    {
        count += 1;
    }
    advDisplay();
}


/// Flicker all LEDs
///
void displayChoiceAllFlicker()
{
//    //const uint8_t flicks = 16;
//    #define flicks 16
//    const uint16_t flicker[flicks] = {1000,100,2000,20,4000,60,8000,10,500,80,4000,10,1500,30,2500,60};
//    
//    static bool switchBetween = true;
//    static uint8_t index = 0;
//    static uint16_t count = 0;
//    
//    if (count == flicker[index])
//    {
//        setDisplayMode(switchBetween ? DisplayLEDs_Off : DisplayLEDs_All);
//        switchBetween = !switchBetween;
//        if (index < (flicks-1))
//            index += 1;        
//        else
//            index = 0;
//        count = 0;
//    }
//    else
//    {
//        count += 1;
//    }

    advDisplay();
}


void displayChoiceLedTest()
{   

    switch (gChoiceAction)
    {
    case ChoiceModeAction_None:
        break;
    case ChoiceModeAction_One:
        advDisplay();
        clearChoiceAction();
        break;
    case ChoiceModeAction_Two:
        // "Fake" going backwards by scrolling fast forward to previous LED
        for (uint8_t i=0 ; i<getModeStateCount() ; i++)
            advDisplay();
        clearChoiceAction();
        break;
    }    
}



/// After the setup function is run this routine 
/// keeps running until the state is changed
///
void displayEventControl()
{
    switch (gDisplayState)
    {
    case DisplayState_Init:
        break;
    case DisplayState_Start:
        displayStart();
        break;
    case DisplayState_HeartFade:
        displayHeartFade();
        break;
    case DisplayState_Menu:
        displayMenu();
        break;
    case DisplayState_Choices:
        switch (gDisplayChoice)
        {
        case DisplayChoice_Comet:         displayChoiceComet();         break;
        case DisplayChoice_ExtScroll:     displayChoiceExtScroll();     break;   
        case DisplayChoice_ExtScrollSlow: displayChoiceExtScrollSlow(); break;
        case DisplayChoice_FadeInOut:     displayChoiceFadeInOut();     break; 
        case DisplayChoice_AllBlink:      displayChoiceAllBlink();      break;
        case DisplayChoice_AllFlicker:    displayChoiceAllFlicker();    break;
        case DisplayChoice_LedTest:       displayChoiceLedTest();       break;
        default:                          displayChoices();             break;
        }
        break;
    }
}


/// When a display state changes, this routine
/// runs the setup function for that state
void setDisplayState(DisplayState displayState)
{
    if (gDisplayState != displayState)
    {
        gDisplayState = displayState;
        switch (gDisplayState)
        {
        case DisplayState_Init:
            break;
        case DisplayState_Start:
            displayStartSwitch();
            break;
        case DisplayState_HeartFade:
            displayHeartFadeSwitch();
            break;
        case DisplayState_Menu:
            displayMenuSwitch();
            break;
        case DisplayState_Choices:
            displayChoicesSwitch();
            break;
        }
    }    
}


/// Initialise the display
///
void initDisplay()
{
    setDisplayState(DisplayState_Start);
}


