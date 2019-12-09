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


#include "pwmControl.h"

#include "eventControl.h"
#include "pwmFunctions.h"
#include "pinFunctions.h"

// Fade control
uint8_t gPwmDutyCycle = 3;
uint8_t gPwmBot = 10;
uint8_t gPwmTop = 130;
uint8_t gPwmInc = 3;

uint8_t gPwmRounds = 0;

bool gPwmEnabled;

void enablePwm()
{
    turnOffPB1();
    turnOffPB2();
    turnOffPB3();
    resetPwmToBot();
    connectPwmChansToIOs();
    gPwmEnabled = true;
}

void disablePwm()
{
    turnOffPB1();
    turnOffPB2();
    turnOffPB3();
    disconnectPwmChansFromIOs();
    gPwmEnabled = false;
}

bool isPwmEnabled()
{
    return gPwmEnabled;
}

void resetPwmToTop()
{
    loadPwmChansWithDutyCycle(gPwmTop);
}

void resetPwmToBot()
{
    loadPwmChansWithDutyCycle(gPwmBot);
}

uint8_t getPwmRounds()
{
    return gPwmRounds;
}

void resetPwmRounds()
{
    gPwmRounds = 0;
}

void advPwmDutyCycle()
{
    static int8_t sign = 1;

    if (gPwmDutyCycle > gPwmTop)
    {
        sign = -1;
    }
    
    if (gPwmDutyCycle < gPwmBot)
    {
        sign = 1;
        gPwmRounds += 1;
    }

    gPwmDutyCycle += (gPwmInc*sign); 
}

void setPwmInc(uint8_t newInc)
{
    gPwmInc = newInc;
}

void updatePwm() {
    advPwmDutyCycle();
    loadPwmChansWithDutyCycle(gPwmDutyCycle);
}

void initPwm()
{
    const uint8_t tickInterval = 20u;
    registerEvent(&updatePwm, tickInterval);
}
