#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdbool.h>
#include "macro.h"
#include "DIO.h"
#include "lcd.h"
#include "keypad.h"
#include "eeprom.h"
#include "led.h"
#include "button.h"
#include "ADC.h"
#include <avr/interrupt.h>//to use bilt in functions in interrupt
#define cc   //common cathode
#include <stdio.h>
#include <math.h>
#include <float.h>
#define past_pressur 0x50
#define past_tempretur 0x60
int main(void)
{
	//initi part
	LCD_inti();
	ADC_init();
	keypad_inti();
LED_init('B',3);
LED_init('B',4);
LED_init('C',0);
	int counter=0  ;
	unsigned long  preassur, temperatue , volt,x=0 ;
	double integralPart, fractionalPart ;
	
	//draw part
	LCD_send_command(64);
	//to send tempreature logo
	LCD_send_data( 0x0A);
	LCD_send_data( 0x0A);
	LCD_send_data( 0x0A);
	LCD_send_data( 0x0A);
	LCD_send_data( 0x1B);
	LCD_send_data( 0x11);
	LCD_send_data( 0x11);
	LCD_send_data( 0x0E);
	 // to send  lines
	LCD_send_data( 0x1C);
	LCD_send_data( 0x00);
	LCD_send_data( 0x1C);
	LCD_send_data( 0x00);
	LCD_send_data( 0x00);
	LCD_send_data( 0x00);
	LCD_send_data( 0x00);
	LCD_send_data( 0x00);
	
	
	//to send to lcd start and logo of tempreture
	LCD_move_cursore(1,6);
	LCD_send_string("Start . . "); 
	_delay_ms(400);
	LCD_move_cursore(2,8);
	LCD_send_data(0);
	_delay_ms(100);
	LCD_send_data(1);
	_delay_ms(100);
	LCD_send_data(' ');
	LCD_send_data(0XDF);
	_delay_ms(1200);
	LCD_clear_screen();
	LCD_move_cursore(1,2);
	//just to initlize frist past tempreature and prressure << to calculate  barmotric prresure in first time "put them randomlyy"
	EEPROM_write(past_pressur , 100);
	EEPROM_write(past_tempretur, 25);
	while(1)
	{
		int arr[3]={NOTPRESSED,NOTPRESSED,NOTPRESSED};
		counter=0;
		//calc part << negative tempreature are considred
		volt=ADC_Read()*2.5;
		temperatue=(ADC_Read()*0.25);
		
		
		//to know + | -
		if(volt>=1000.00){ //mean tempreature is positive
			temperatue=(volt-1000)/10;
		}
		if(volt< 1000.00) { // mean tempreature is negative
			temperatue=((1000-volt)/10);
		}
		
		// to indicate tempreature what will be?? "know from light of led"
		if( volt< 1000.00 ){ //cold
			LED_ON('C',0);
			_delay_ms(2000);
			LED_OFF('C',0);
		}
		 if( (temperatue>=14.00) && (temperatue<=83.00) && (volt>=1000.00) ){ //moderate
			LED_ON('B',3);
			_delay_ms(2000);
			LED_OFF('B',3);
		}
		if( (temperatue>=85.00) && (temperatue<=150.00)){ // hot
			LED_ON('B',4);
			_delay_ms(2000);
			LED_OFF('B',4);
		}
		
		LCD_send_string("UNIT ?");
		LCD_move_cursore(2,1);
		LCD_send_string("1:");
		LCD_send_data(0xDF);
		LCD_send_string("C");
		LCD_move_cursore(2,7);
		LCD_send_string("2:");
		LCD_send_data(0xDF);
		LCD_send_string("F");
		LCD_move_cursore(2,13);
		LCD_send_string("3:K");
		_delay_ms(1500);
		//LCD_clear_screen();
		do
		{
			arr[counter]=keypad_check_press();
			
		} while(arr[counter]==NOTPRESSED);
		LCD_clear_screen();
		LCD_move_cursore(1,3);
		
		LCD_send_string("temperature : ");
		LCD_move_cursore(2,6);
	
		
				
		if(arr[counter]=='1'){ // celeuis
		   // temperatue=(ADC_Read()*0.25);
			//temperatue-=0.25;
			
			}
			
		else if(arr[counter]=='2'){ // fehrenhight
	        temperatue+=273.15;}
			
	    if(arr[counter]=='3'){ // kelvin
			x=(5/9)+273.15;
			temperatue+=273.15;
			temperatue*=x;}
         //   temperatue= (((ADC_Read()*0.25)+273.15)*(5/9))+273.15 ;}
		
			if(volt>=1000.00){ //mean tempreature is positive
			
		}
		 if(volt< 1000.00) { // mean tempreature is negative
		LCD_move_cursore(2,5);
		LCD_send_data('-');
	}
	
	//to display number to tempreature
	LCD_move_cursore(2,6);
	fractionalPart = modf(temperatue, &integralPart); //partitioning result into 2 rejon , integre rejon stored in integralPart variable
	lcd_sendFloat(integralPart); //show int part
	LCD_send_data('.');
	fractionalPart*=1000;
	lcd_sendFloat(fractionalPart); //show numbers after dot
	
	//_delay_ms(500);
	if(arr[counter]=='1'){ // celeuis
LCD_send_data(' ');
LCD_send_data(0xDF);
LCD_send_data(0x43);

}

else if(arr[counter]=='2'){ // fehrenhight
	       LCD_send_data(0xDF);
		   LCD_send_string(" F");
		 
		   }
			
	    if(arr[counter]=='3'){ // kelvin
            LCD_send_string(" K");}
	_delay_ms(4000);
	//_delay_ms(1500);
	LCD_clear_screen();
	LCD_move_cursore(1,1);
LCD_send_string("Barometric Press:");
LCD_move_cursore(2,6);
//LCD_send_data(preassur); << to send it on lcd
fractionalPart = modf(preassur, &integralPart); //partitioning result into 2 rejon , integre rejon stored in integralPart variable
lcd_sendFloat(integralPart); //show int part
LCD_send_data('.');
fractionalPart*=1000;
lcd_sendFloat(fractionalPart); //show numbers after dot
LCD_send_data(' ');
LCD_send_data(0xE6);
EEPROM_write(past_pressur,preassur); //<<to updateee
EEPROM_write(past_tempretur, (temperatue));

_delay_ms(4000);
//_delay_ms(1500);
LCD_clear_screen();

	}//end of while
}//end of main
	

	