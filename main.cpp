/******************************************************************
BINARY UP COUNTER WITH LEDs
===========================
In thsi project 8 LEDs are conencted to PORT C. The LEDs count up
in binary every second.
Author: Dogan Ibrahim
Date : August 2018
File : Counter
*******************************************************************/

#include "mbed.h"
using ThisThread::sleep_for;
//Serial MyPC(USBTX, USBRX);

#define timeout 1s

// HARDWARE
// INPUTS
DigitalIn button(PC_13); // BUTTON1 is input

DigitalIn adult_in_btn(PC_0, PullUp); // BUTTON1 is input
DigitalIn adult_out_btn(PC_1, PullUp); // BUTTON1 is input
DigitalIn fire_btn(PB_0, PullUp); // BUTTON1 is input

// OUTPUTS
//Define LEDs
DigitalOut STOP_LED(ARDUINO_UNO_D5);
DigitalOut Chair1_LED(ARDUINO_UNO_D2);
DigitalOut Chair2_LED(ARDUINO_UNO_D3);
DigitalOut Chair3_LED(ARDUINO_UNO_D4);
DigitalOut Clock_LED(ARDUINO_UNO_D1);

BusOut seats(ARDUINO_UNO_D13, ARDUINO_UNO_D12, ARDUINO_UNO_D11, ARDUINO_UNO_D10, ARDUINO_UNO_D9, ARDUINO_UNO_D8,ARDUINO_UNO_D7, ARDUINO_UNO_D6);

//VARIABLES
int CNT = 0; // CNT = 0

// PROCEDURES

void adult_in();
void adult_out();
void fire();

int main()
{
    while(1) // DO forever
    {
        if(adult_in_btn == 0) // If button is pressed
        //if(button == 0) // If button is pressed
        {
            adult_in();
        }
        
        else if(adult_out_btn == 0) // If button is pressed
        {
            adult_out();
        }
        
        else if(fire_btn == 0) // If button is pressed
        {
            fire();
        }
        
    }
}

void adult_in()
{
    if(CNT > 254) // CNT back to 0
    {
        STOP_LED = 1;
        sleep_for(timeout);
        STOP_LED = 0;
    }
    else
    {
        CNT = CNT << 1; // Incfement CNT
        CNT = CNT | 01; // AND to CNT to light shifted LEDs
        seats = CNT; // Turn ON LED
    }
    sleep_for(timeout);
}

void adult_out()
{
    if(CNT <= 0) // CNT back to 0
    {
        STOP_LED = 1;
        sleep_for(timeout);
        STOP_LED = 0;
    }
    else if(CNT > 0) 
    {
        CNT = CNT >> 1; // Decfement CNT
        seats = CNT; // Turn ON LED
        sleep_for(timeout);
    }
}

void fire()
{
	STOP_LED = 1;
	Chair1_LED = Chair2_LED = Chair3_LED = 0;
	while (seats > 0)
	{
		CNT = CNT >> 1;
        seats = CNT;
		sleep_for(timeout);
	}
    STOP_LED = 0;
}