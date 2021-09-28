/***********************************************************************
 * 
 * Blink a LED and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
/* The preprocessor will process directives that are inserted into the C
 * source code. These directives allow additional actions to be taken on
 * the C source code before it is compiled into object code. Directives
 * are not part of the C language itself.
 *
 * Preprocessor directives begin with a pound (#) symbol and may have 
 * several arguments. Do NOT put a semicolon character at the end of 
 * directives. This is a common mistake.
 */
#define LED_GREEN   PB5 // AVR pin where green LED is connected
#define SHORT_DELAY 300 // Delay in milliseconds
#define LONG_DELAY	900 // Delay in milliseconds
#define END			2100 // Delay in milliseconds
#define DOT			300 // Duration of a dot
#define DASH		900 // Duration of a dash
#ifndef F_CPU           // Preprocessor directive allows for conditional
                        // compilation. The #ifndef means "if not defined".
# define F_CPU 16000000 // CPU frequency in Hz required for delay
#endif                  // The #ifndef directive must be closed by #endif

/* Includes ----------------------------------------------------------*/
/* Include another C language file into the current file at the location
 * of the #include statement prior to compiling the source code.
 */
#include <util/delay.h> // Functions for busy-wait delay loops
#include <avr/io.h>     // AVR device-specific IO definitions

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
    DDRB = DDRB | (1<<LED_GREEN);

    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<LED_GREEN);

    // Infinite loop
    while (1)
    {
        // Invert LED in Data Register
        // PORTB = PORTB and 0010 0000
        PORTB = PORTB & ~(1<<LED_GREEN);
		
		// Letter D
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DASH);					// 3 units 
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(SHORT_DELAY);				// 1 unit
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DOT);						// 1 unit
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(SHORT_DELAY);				// 1 unit
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DOT);						// 1 unit
		
		// Gap between the letters
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(LONG_DELAY);				// 1 unit
		
		// Letter E
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DOT);						// 1 unit
		
		// Gap between the letters
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(LONG_DELAY);				// 3 units
		
		// Number 2
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DOT);						// 1 unit
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(SHORT_DELAY);				// 1 unit
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DOT);						// 1 unit
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(SHORT_DELAY);				// 1 unit
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DASH);					// 3 units
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(SHORT_DELAY);				// 1 unit
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DASH);					// 3 units
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(SHORT_DELAY);				// 1 unit
		PORTB = PORTB ^ (1<<LED_GREEN);		// Led on
		_delay_ms(DASH);					// 3 units
		
		// Gap between the letters
		PORTB = PORTB & ~(1<<LED_GREEN);	// Led off
		_delay_ms(END);						// 7 units
    }

    // Will never reach this
    return 0;
}


