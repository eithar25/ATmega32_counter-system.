/*
 * final.c
 *
 *  Created on: 27 Jul 2025
 *      Author: Eithar
 */

#include <avr/io.h>
#include <util/delay.h>

void Eta32mini_SevenSegment_Display(unsigned char value)
{
	switch(value)
	{
	case 0:
		PORTA |= (1<<1);
		PORTA |= (1<<2);
		PORTA |= (1<<3);
		PORTA |= (1<<4);
		PORTA |= (1<<5);
		PORTA |= (1<<6);
		PORTA &= ~(1<<7);
		break;
	case 1:
		PORTA &= ~(1<<1);
		PORTA |= (1<<2);
		PORTA |= (1<<3);
		PORTA &= ~(1<<4);
		PORTA &= ~(1<<5);
		PORTA &= ~(1<<6);
		PORTA &= ~(1<<7);
		break;
	case 2:
		PORTA |= (1<<1);
		PORTA |= (1<<2);
		PORTA &= ~(1<<3);
		PORTA |= (1<<4);
		PORTA |= (1<<5);
		PORTA &= ~(1<<6);
		PORTA |= (1<<7);
		break;
	case 3:
		PORTA |= (1<<1);
		PORTA |= (1<<2);
		PORTA |= (1<<3);
		PORTA |= (1<<4);
		PORTA &= ~(1<<5);
		PORTA &= ~(1<<6);
		PORTA |= (1<<7);
		break;
	case 4:
		PORTA &= ~(1<<1);
		PORTA |= (1<<2);
		PORTA |= (1<<3);
		PORTA &= ~(1<<4);
		PORTA &= ~(1<<5);
		PORTA |= (1<<6);
		PORTA |= (1<<7);
		break;
	case 5:
		PORTA |= (1<<1);
		PORTA &= ~(1<<2);
		PORTA |= (1<<3);
		PORTA |= (1<<4);
		PORTA &= ~(1<<5);
		PORTA |= (1<<6);
		PORTA |= (1<<7);
		break;
	case 6:
		PORTA |= (1<<1);
		PORTA &= ~(1<<2);
		PORTA |= (1<<3);
		PORTA |= (1<<4);
		PORTA |= (1<<5);
		PORTA |= (1<<6);
		PORTA |= (1<<7);
		break;
	case 7:
		PORTA |= (1<<1);
		PORTA |= (1<<2);
		PORTA |= (1<<3);
		PORTA &= ~(1<<4);
		PORTA &= ~(1<<5);
		PORTA &= ~(1<<6);
		PORTA &= ~(1<<7);
		break;
	case 8:
		PORTA |= (1<<1);
		PORTA |= (1<<2);
		PORTA |= (1<<3);
		PORTA |= (1<<4);
		PORTA |= (1<<5);
		PORTA |= (1<<6);
		PORTA |= (1<<7);
		break;
	case 9:
		PORTA |= (1<<1);
		PORTA |= (1<<2);
		PORTA |= (1<<3);
		PORTA &= ~(1<<4);
		PORTA &= ~(1<<5);
		PORTA |= (1<<6);
		PORTA |= (1<<7);
		break;
	}
}






void LED_BINARY(unsigned char BIN)
{
	switch(BIN)
	{
	case 0:
		PORTC &= ~ (1<<0);
		PORTC &= ~ (1<<1);
		PORTC &= ~ (1<<2);
		break;
	case 1:
		PORTC |= (1<<0);
		PORTC &= ~ (1<<1);
		PORTC &= ~ (1<<2);
		break;
	case 2:
		PORTC &= ~ (1<<0);
		PORTC |= (1<<1);
		PORTC &= ~(1<<2);
		break;
	case 3:
		PORTC |= (1<<0);
		PORTC |= (1<<1);
		PORTC &= ~(1<<2);
		break;
	case 4:
		PORTC &= ~ (1<<0);
		PORTC &= ~ (1<<1);
		PORTC |= (1<<2);
		break;
	case 5:
		PORTC |= (1<<0);
		PORTC &= ~ (1<<1);
		PORTC |=(1<<2);
		break;
	case 6:
		PORTC &= ~ (1<<0);
		PORTC |= (1<<1);
		PORTC |=(1<<2);
		break;
	case 7:
		PORTC |= (1<<0);
	    PORTC |= (1<<1);
	    PORTC |=(1<<2);
		break;

	}
}









int main(void)
{
	unsigned char count = 0;
	unsigned char enable = 1;

	DDRD  &= ~(1<<2) & ~(1<<3) & ~(1<<4) & ~(1<<5) ;     //push buttons
	DDRC  |= (1<<5);   //buzzer
	DDRC  |= (1<<0);  //led
	DDRC  |= (1<<1);  //led
	DDRC  |= (1<<2);  //led
    DDRC  |= (1<<6);
	PORTC |= (1<<6);//7-segment control

	DDRA  |= 0xFE;// 7-segment leds from PA1 --> PA7

	Eta32mini_SevenSegment_Display(count); // Display ZERO value on the 7-segment at the beginning

	while(1)
	{
		if( !(PIND & (1<<PD2)) ) // increment
		{
			_delay_ms(30);
			if( !(PIND & (1<<PD2)) ) //second check due to switch bouncing
			{
				if (enable == 1){
				if(count != 7)
				{
					count++;
					Eta32mini_SevenSegment_Display(count);
					LED_BINARY(count);
								}
				else if(count == 7){
									PORTC  |= (1<<5);   //1st iteration
									_delay_ms(500);
									PORTC  &= ~(1<<5);
									_delay_ms(500);

									PORTC  |= (1<<5);   //2nd iteration
									_delay_ms(500);
									PORTC  &= ~(1<<5);
									_delay_ms(500);

									PORTC  |= (1<<5);   //3rd iteration
									_delay_ms(500);
									PORTC  &= ~(1<<5);
									_delay_ms(500);
								}
				}

			}
			while( !(PIND & (1<<PD2)) ){} // wait until switch is released
		}
		else if(!(PIND & (1<<PD3))) //decrement
		{
			_delay_ms(30);
			if( !(PIND & (1<<PD3)) ) //second check due to switch bouncing
			{
				if (enable == 1){
				if(count != 0)
				{
					// decrement 7-segment every press
					count--;
					Eta32mini_SevenSegment_Display(count);
					LED_BINARY(count);
				}
				else if(count == 0){
					PORTC  |= (1<<5);   //1st iteration
					_delay_ms(500);
					PORTC  &= ~(1<<5);
					_delay_ms(500);

					PORTC  |= (1<<5);   //2nd iteration
					_delay_ms(500);
					PORTC  &= ~(1<<5);
					_delay_ms(500);

					PORTC  |= (1<<5);   //3rd iteration
					_delay_ms(500);
					PORTC  &= ~(1<<5);
					_delay_ms(500);
				}


			}
			}
			while( !(PIND & (1<<PD3)) ){} // wait until switch is released
		}
		else if(!(PIND & (1<<PD4))) //pause
		{
			_delay_ms(30);
			if( !(PIND & (1<<PD4)) ) //second check due to switch bouncing
			{
				if(enable == 1){
					enable = 0;
				}
				else if (enable == 0){
					enable = 1;
				}

			}
			while( !(PIND & (1<<PD4)) ){} // wait until switch is released

		}

		if( !(PIND & (1<<PD5)) ) // reset
				{
					_delay_ms(30);
					if( !(PIND & (1<<PD5)) ) //second check due to switch bouncing
					{
					    count = 0;
					    Eta32mini_SevenSegment_Display(count);
					    LED_BINARY(count);
					    enable = 1;
					    for(int i=0; i<3; i++){
					    	PORTC|=0x07;
					    	_delay_ms(700);
					    	PORTC &=~(0x07);
					    	_delay_ms(700);
					    }

					}
					while( !(PIND & (1<<PD5)) ){} // wait until switch is released
				}


	}

}


