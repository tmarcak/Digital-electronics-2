/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5     // AVR pin where green LED is connected
#define LED_BLUE    PC1     // AVR pin where green LED is connected
#define BLINK_DELAY 500
#ifndef F_CPU
# define F_CPU 16000000     // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
// #include <avr/sfr_defs.h>
/* Functions ---------------------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle two LEDs when a push button is pressed.
 * Returns:  none
 **********************************************************************/
int main(void)
{
	// Green LED at port B
	// Set pin as output in Data Direction Register...
	DDRB = DDRB | (1<<LED_GREEN);
	// ...and turn LED off in Data Register
	PORTB = PORTB & ~(1<<LED_GREEN);

	// Blue LED at port C
	DDRC = DDRC | (1<<LED_BLUE);
	PORTC = PORTC & ~(1<<LED_BLUE);

	// Infinite loop
	while (1)
	{
		// Pause several milliseconds
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB ^ (1<<LED_GREEN);
		PORTC = PORTC ^ (1<<LED_BLUE);
		
	}

	// Will never reach this
	return 0;
}