/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "util/delay.h"

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update stopwatch value on LCD display when 8-bit 
 *           Timer/Counter2 overflows.
 * Returns:  none
 **********************************************************************/
 
/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update stopwatch value on LCD display when 8-bit 
 *           Timer/Counter2 overflows.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("Hello World");
    lcd_putc('!');
        _delay_ms(1200);
        lcd_clrscr();
        
        _delay_us(800);
        
        lcd_gotoxy(1, 0);
        lcd_puts("00:00.0");
        lcd_gotoxy(11, 0);
       	lcd_putc('a');
       	lcd_gotoxy(1, 1);
       	lcd_putc('b');
       	lcd_putc(0);
       	lcd_gotoxy(11, 1);
       	lcd_putc('c');
       	_delay_ms(2000);
        
    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set the overflow prescaler to 16 ms and enable interrupt
    TIM2_overflow_16ms();
    TIM2_overflow_interrupt_enable();
	
	TIM0_overflow_16ms();
	TIM0_overflow_interrupt_enable();
	
	TIM1_overflow_262ms();
	TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

void lcd_update_number(uint8_t num, uint8_t pos)
{
    char lcd_str[2] = "  ";
    itoa(num, lcd_str, 10);
    if (num < 10)
    {
        lcd_gotoxy(1 + pos*3, 0);
        if (pos == 2)
        {
            lcd_putc(lcd_str[0]);
        }
        else
        {
            lcd_putc('0');
            lcd_putc(lcd_str[0]);
            
        }
    }
    else
    {
        lcd_gotoxy(1 + pos*3, 0);
        if (pos == 2)
        lcd_putc(lcd_str[0]);
        else
        lcd_puts(lcd_str);
    }
}

/**********************************************************************
 * Function: Timer/Counter2 overflow interrupt
 * Purpose:  Update the stopwatch on LCD display every sixth overflow,
 *           ie approximately every 100 ms (6 x 16 ms = 100 ms).
 **********************************************************************/
ISR(TIMER2_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
    static uint8_t tens = 0;        // Tenths of a second
    static uint8_t secs = 0;        // Seconds
    static uint8_t mins = 0;        // Minutes
    char lcd_string[2] = "  ";      // String for converting numbers by itoa()

    number_of_overflows++;
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;
               tens++;
               
               lcd_update_number(tens, 2);
               
              if (tens == 10)
               {
                   tens = 0;
                   secs++;
                   lcd_update_number(tens, 2);
                   lcd_update_number(secs, 1);
                   if (secs == 60)
                   {
                       mins++;
                       secs = 0;
                       lcd_update_number(secs, 1);
                       lcd_update_number(mins, 0);
                   }
                   if (mins == 60)
                   {
                       mins = 0;
                       lcd_update_number(mins, 0);
                  }
                   
               }



    }
    
}