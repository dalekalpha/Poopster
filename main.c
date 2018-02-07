/*
 * LEDblinker.c
 *
 * Created: 13/11/2017 14.01.15
 * Author : Dam-Lenovo
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0b00000001;
    while (1) 
    {
		PORTB ^= 0b00000001;
		_delay_ms(500);
    }
} 

