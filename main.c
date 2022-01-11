/*
 * main.c
 *
 *  Created on: Jan 10, 2022
 *      Author: Abdelrahman Mohamed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "Interrupt_interface.h"
#include "KEYPAD_interface.h"

#include "Motor.h"



#define SPEED_BUTTON	8
#define	MOVE_BUTTON		2
#define RIGHT_BUTTON	6
#define LEFT_BUTTON		4

#define PRESSED			1
#define NOT_PRESSED		0

void MOVE_REV(void);
void MOVE_FWD(void);
void MOVE_LEFT(void);
void MOVE_RIGHT(void);
void MOTORS_OFF();

void main()
{
	GlobalInerruptEnable();
	 KPD_init();
	 MOTOR_init(MOTOR_1);
	 MOTOR_init(MOTOR_2);

	 uint8_t Speed_level =0;
	 uint8_t key=0;


	 DIO_SETpinDir(DIO_PORTB,4,1);
	 DIO_SETpinDir(DIO_PORTB,5,1);
	 DIO_SETpinDir(DIO_PORTB,6,1);
	 DIO_SETpinDir(DIO_PORTB,7,1);

	while(1)
	{
		if( SPEED_BUTTON == KPD_u8GetPressedKey())
		{
			Speed_level++;
			if(Speed_level >4)
			{
				Speed_level =1;
			}
			switch (Speed_level)
			{
			case  1:
				DIO_SETpinVal(DIO_PORTB,4,1);
				DIO_SETpinVal(DIO_PORTB,5,0);
				DIO_SETpinVal(DIO_PORTB,6,0);
				DIO_SETpinVal(DIO_PORTB,7,0);
			break;
			case  2:
				DIO_SETpinVal(DIO_PORTB,4,0);
				DIO_SETpinVal(DIO_PORTB,5,1);
				DIO_SETpinVal(DIO_PORTB,6,0);
				DIO_SETpinVal(DIO_PORTB,7,0);
			break;
			case 3:
				DIO_SETpinVal(DIO_PORTB,4,0);
				DIO_SETpinVal(DIO_PORTB,5,0);
				DIO_SETpinVal(DIO_PORTB,6,1);
				DIO_SETpinVal(DIO_PORTB,7,0);
			break;
			case  4:
				DIO_SETpinVal(DIO_PORTB,4,0);
				DIO_SETpinVal(DIO_PORTB,5,0);
				DIO_SETpinVal(DIO_PORTB,6,0);
				DIO_SETpinVal(DIO_PORTB,7,1);
			break;
			}
			while(SPEED_BUTTON == KPD_u8GetPressedKey())
			{

			}
		}

		while(MOVE_BUTTON == KPD_u8GetPressedKey() )
		{
			if(Speed_level ==1)
			{
				MOTOR_speed(30);
				MOVE_FWD();
			}
			else if (Speed_level == 2 )
			{
				MOTOR_speed(60);
				MOVE_FWD();
			}
			else if (Speed_level == 3 )
			{
				MOTOR_speed(90);
				MOVE_FWD();
			}
			else if (Speed_level == 4 )
			{
				MOTOR_speed(30);
				MOVE_REV();
			}
		}
		MOTORS_OFF();
		while(RIGHT_BUTTON == KPD_u8GetPressedKey() )
		{
			MOTOR_speed(30);
			MOVE_RIGHT();
		}
		MOTORS_OFF();
		while(LEFT_BUTTON == KPD_u8GetPressedKey() )
		{
			MOTOR_speed(30);
			MOVE_LEFT();
		}
		MOTORS_OFF();


	}
}


void MOVE_REV(void)
{
	MOTOR_direction(MOTOR_1, REV);
	MOTOR_direction(MOTOR_2, REV);
}

void MOVE_FWD(void)
{
	MOTOR_direction(MOTOR_1, FWD);
	MOTOR_direction(MOTOR_2, FWD);
}

void MOVE_RIGHT(void)
{
	MOTOR_direction(MOTOR_1, FWD);
	MOTOR_direction(MOTOR_2, REV);
}

void MOVE_LEFT(void)
{
	MOTOR_direction(MOTOR_1, REV);
	MOTOR_direction(MOTOR_2, FWD);
}

void MOTORS_OFF()
{
	MOTOR_off(MOTOR_1);
	MOTOR_off(MOTOR_2);
}
