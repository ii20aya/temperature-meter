/*
 * eeprom.c
 *
 * Created: 11/17/2023 5:59:44 PM
 *  Author: HD STORE
 */ 
#include "macro.h"
#include <avr/io.h>


void EEPROM_write(unsigned short address , unsigned char data){
	EEARL=(char)address;
	EEARH=(char)(address>>8); // shift right to access another 8 bit
	
	EEDR=data;
	//start write process
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);
	while(READ_BIT(EECR,EEWE)==1); // wait until write processing is done
	
}

/////////////////////////////
unsigned char EPROM_read(const unsigned short address){
	EEARL=(char)address;
	EEARH=(char)(address>>8);
	SET_BIT(EECR,EERE);
	return EEDR;
	
}