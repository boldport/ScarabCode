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

#include <stdint.h>

/// A reference to function
typedef void(*EventFn)(void);

/// Initialise the event system
///
void initEvents(void);

/// Register and event function with an initial interval
///
void registerEvent(EventFn eventFn, uint32_t interval);

/// Update the event interval for a registered function
///
void setEventInterval(EventFn eventFn, uint32_t interval);

/// Run the event loop (never return))
///
void eventLoop(void);
