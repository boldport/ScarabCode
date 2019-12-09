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


#include "pwmFunctions.h"

// Disconnect all 3 channels from IOs
void disconnectPwmChansFromIOs() {
    TCA0.SINGLE.CTRLB = ~(1 << TCA_SINGLE_CMP0EN_bp)
                      & ~(1 << TCA_SINGLE_CMP1EN_bp)
                      & ~(1 << TCA_SINGLE_CMP2EN_bp);
                      
//    TCA0.SINGLE.CTRLB &= ~(1 << TCA_SINGLE_CMP0EN_bp);
//    TCA0.SINGLE.CTRLB &= ~(1 << TCA_SINGLE_CMP1EN_bp);
//    TCA0.SINGLE.CTRLB &= ~(1 << TCA_SINGLE_CMP2EN_bp);
}

// Connect all 3 channels to IOs
void connectPwmChansToIOs() {
//    TCA0.SINGLE.CTRLB = (1 << TCA_SINGLE_CMP0EN_bp)
//                      | (1 << TCA_SINGLE_CMP1EN_bp)
//                      | (1 << TCA_SINGLE_CMP2EN_bp);

    TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP0EN_bp);
    TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP1EN_bp);
    TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP2EN_bp);
}

// Load all PWM channels with duty cycle value
void loadPwmChansWithDutyCycle(PWM_0_register_t duty_value) {
    TCA0.SINGLE.CMP0BUF = duty_value;
    TCA0.SINGLE.CMP1BUF = duty_value;
    TCA0.SINGLE.CMP2BUF = duty_value;
}

