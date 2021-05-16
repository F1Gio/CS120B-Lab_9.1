/*	Author:gturr001,  Giovany Turrubiartes
 *  Partner(s) Name: 
 *	Lab Section: 023
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
enum SM1_States {SM1_Start, SM1_PB0, SM1_OFF1, SM1_PB1, SM1_OFF2, SM1_PB2, SM1_Start } SM1_State;
enum SM2_States {SM2_Start, SM1_PB3 } SM2_State;
enum SM3_States {SM3_SET} SM3_State;

unsigned char LED = 0x00;
unsigned char BLED = 0x00;
unsigned char TLED = 0x00;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;

}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void ThreeLED() { 

}

void BlinkingLED() {
	switch(SM2_State) {
		case SM2_Start:
			SM2_State = SM2_PB3;
			break;

		case SM2_PB3:
			SM2_State = SM2_Start;
			break;

		default: 
			SM1_Start;
			break;

	}

	switch(SM2_State) {
		case SM2_Start:
			BLED = 0x00;
			break;

		case SM2_PB3:
			BLED = 0x04;
			break;

	}

}


void CombineLED() {

}


int main(void) {

	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();

    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    while (1) {


	    ThreeLED();
	    BlinkingLED();
	    CombineLED();


	    while (!TimerFlag);
	     TimerFlag = 0;
	    
    

    }
  
}
