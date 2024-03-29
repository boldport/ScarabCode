/**
 * \file
 *
 * \brief Driver initialization.
 *
 (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/*
 * Code generated by START.
 *
 * This file will be overwritten when reconfiguring your START project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <system.h>

void PWM_0_initialization(void)
{

	// Set pin direction to output
	PB3_set_dir(PORT_DIR_OUT);

	PB3_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	/* set the alternate pin mux */
	PORTMUX.CTRLC |= PORTMUX_TCA00_bm;

	// Set pin direction to output
	PB1_set_dir(PORT_DIR_OUT);

	PB1_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	// Set pin direction to output
	PB2_set_dir(PORT_DIR_OUT);

	PB2_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	PWM_0_init();
}

void TIMER_0_initialization(void)
{

	TIMER_0_init();
}

void TIMER_1_initialization(void)
{

	TIMER_1_init();
}

/**
 * \brief System initialization
 */
void system_init()
{
	mcu_init();

	/* PORT setting on PA1 */

	// Set pin direction to output
	PA1_set_dir(PORT_DIR_OUT);

	PA1_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    true);

	/* PORT setting on PA2 */

	// Set pin direction to output
	PA2_set_dir(PORT_DIR_OUT);

	PA2_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    true);

	/* PORT setting on PA3 */

	// Set pin direction to output
	PA3_set_dir(PORT_DIR_OUT);

	PA3_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    true);

	/* PORT setting on PA4 */

	// Set pin direction to output
	PA4_set_dir(PORT_DIR_OUT);

	PA4_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    true);

	/* PORT setting on PA5 */

	// Set pin direction to output
	PA5_set_dir(PORT_DIR_OUT);

	PA5_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    true);

	/* PORT setting on PA6 */

	// Set pin direction to output
	PA6_set_dir(PORT_DIR_OUT);

	PA6_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    true);

	CLKCTRL_init();

	Timer_init();

	PWM_0_initialization();

	TIMER_0_initialization();
    
    TIMER_1_initialization();

	CPUINT_init();

	SLPCTRL_init();

	BOD_init();
}
