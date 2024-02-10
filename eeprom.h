/*
 * eeprom.h
 *
 * Created: 11/17/2023 5:59:29 PM
 *  Author: HD STORE
 */ 


unsigned char EPROM_read(const unsigned short address);

void EEPROM_write(unsigned short address , unsigned char data);