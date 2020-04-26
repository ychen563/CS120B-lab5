/*	Author: ychen563
 *	Lab Section: 024
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states{Start, Wait, Incre, Decre, Reset} state;
unsigned char cnt = 0;

void Tick(){
    unsigned char tmpA = ~PINA & 0x03;
    switch(state){//Transitions
        case Start:
            cnt = 0x00;
            state = Wait;
            break;
        case Wait:
            if(tmpA == 0x00){
                state = Wait;
            }
            else if(tmpA == 0x01){
                state = Incre;
                if (cnt <= 0x08){cnt++;}
            }
            else if(tmpA == 0x02){
                state = Decre;
                if (cnt > 0x00){cnt--;}
            }
            else if(tmpA == 0x03){
                state = Reset;
            }
            break;
        case Incre:
            if(tmpA == 0x00 || tmpA == 0x02){
                state = Wait;
            }
            else if (tmpA == 0x01){
            	state = Incre;
            }
            else if (tmpA == 0x03){
            	state = Reset;
            }
            break;
        case Decre:
            if (tmpA == 0x00 || tmpA == 0x01){
            	state = Wait;
            }
            else if(tmpA == 0x02){
            	state = Decre;
            }
            else {
            	state = Reset;
            }
            break;
        case Reset:
            if (tmpA == 0x03){
            	state = Reset;
            }
            else {
                state = Wait;
            }
            cnt = 0;
            break;
        default:
            state = Start;
            break;
    }//Transitions
    switch(state){//State actions
        case Start:
            break;
        case Wait:
            break;
        case Incre:
            break;
        case Decre:
            break;
        case Reset:
            break;
        default:
            break;
    }//State actions
    
    PORTC = cnt;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
    /* Insert your solution below */
    state = Start;
    while (1) {Tick();}
    return 0;
}
