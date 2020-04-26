/*	Author: ychen563
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
/*This line is for pull testing*/
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states{Start,Init, ONPRESS, ONRELEASE} state;

	unsigned char tmpA;
	unsigned char tmpB;
	unsigned char tmp = 0x00;

void Tick(){
	tmp = tmpA | tmpB;
	unsigned char input = ~PINA & 0x01;
	switch(state){//Transition
		case Start:
			state = Init;
			break;
		case Init:
			if (!input){
				state = Init;
			}
			else {
				tmp = 0x21;
				tmpA = 0x20;
				tmpB = 0x01;
				state = ONPRESS;
			}
			break;
		case ONPRESS:
			if (input){
				state = ONPRESS;
			}
			else {
				state = ONRELEASE;
			}
			break;
		case ONRELEASE:
			if (!input){
				state = ONRELEASE;
			}
			else {
				                      
			       	tmpA = tmpA >> 1;
                        	tmpB = tmpB << 1;
                        	if(tmpA < 0x08 && tmpB > 0x04){
                                	tmpA = 0x20;
                                	tmpB = 0x01;
                        	}
                        	tmp = tmpA | tmpB;
				state = ONPRESS;
			}
			break;
		default:
			state = Start;
			break;
	}//Transition
	switch(state){//State Actions
		case Start:
			break;
		case Init:
			break;
		case ONPRESS:
			break;
		case ONRELEASE:
			break;
		default:
			break;
	}//State Actions
	PORTC = tmp;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    
    state = Start;
    while(1){
    	Tick();
    }
    return 0;
}
