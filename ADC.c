/*
 * ADC.c
 *
 * Created: 2/5/2024 1:21:55 PM
 *  Author: HD STORE
 */ 
#include <avr/io.h>
#include "macro.h"
#include "ADC.h"
#include <avr/io.h>
#include <stdio.h>
void ADC_init(void)
{
	SET_BIT(ADMUX,REFS0); //configure VREF
	SET_BIT(ADMUX,REFS1);
	//SET_BIT(ADMUX,MUX0)
	SET_BIT(ADMUX,MUX4);
	
	SET_BIT(ADCSRA,ADEN); // enable ADC
	/* adjust ADC clock*/
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
}
unsigned short ADC_Read(void)
{
	unsigned short read_val;
	
	SET_BIT(ADCSRA,ADSC);
	while(READ_BIT(ADCSRA,ADIF)==0);//stay in your position till ADIF become 1 << mean conversion finish
	SET_BIT(ADCSRA,ADIF); // clear ADIF
	read_val=(ADCL);
	read_val|=(ADCH<<8);
	return read_val ;
}