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


#include "eventControl.h"

#include "timer.h"

#include <string.h>

struct EventState {
    EventFn eventFn;
    uint32_t next;
    uint32_t interval;
};

//const uint8_t cEventStateCount = 5; // Unsupported by XC8 :/
#define cEventStateCount 5

struct EventState gEventStates[cEventStateCount] = {};


void initEvents(void)
{
    memset(gEventStates, 0, sizeof(gEventStates));
}

void registerEvent(EventFn eventFn, uint32_t interval)
{
    const uint32_t next = getCurrentTime() + interval;
    struct EventState eventState = {eventFn, next, interval};
    
    for (uint8_t i = 0; i < cEventStateCount; ++i)
    {
        if (gEventStates[i].eventFn == 0)
        {
            gEventStates[i] = eventState;
            break;
        }
    }
}

void setEventInterval(EventFn eventFn, uint32_t interval)
{
    for (uint8_t i = 0; i < cEventStateCount; ++i)
    {
        if (gEventStates[i].eventFn == 0)
        {
            break;
        }
        else if (gEventStates[i].eventFn == eventFn)
        {
            gEventStates[i].next = getCurrentTime() + interval;
            gEventStates[i].interval = interval;
            break;
        }
    }
}

void eventLoop(void)
{
    while (1)
    {
        const uint32_t currentTime = getCurrentTime();
        
        for (uint8_t i = 0; i < cEventStateCount; ++i)
        {
            if (gEventStates[i].eventFn == 0)
            {
                break;
            }
            else if ((int32_t)(gEventStates[i].next - currentTime) <= 0)
            {
                gEventStates[i].eventFn();
                gEventStates[i].next = currentTime + gEventStates[i].interval;
            }
        }
        while (currentTime == getCurrentTime()) {}
    }
}
