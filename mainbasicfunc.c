/*
 * SemesterProject.c
 *
 * Created: 15/11/2017 09.42.14
 * Author : Dam-Lenovo
 */ 

/*
Hvad skal der laves før programmet kan bruges?
Knapperne skal bindes til pins.
Al kode omkring knapperne skal skrives om.
Der skal skrives kode til lampernes opførsel.
*/

#include <avr/io.h>
#include <util/delay.h>

int LeftButtonA = (PINC & 0b00001000);
int LeftButtonB = (PIND & 0b00001000);
int RightButtonA = (PINC & 0b00000100);
int RightButtonB = (PIND & 0b00000100);
int AttackButtonA = (PINC & 0b00000010);
int AttackButtonB = (PINC & 0b00000001);

int TimerALED = (PINB ^= 0b00000001);
int TimerBLED = (PIND ^= 0b10000000);
int TimerCLED = (PIND ^= 0b01000000);
int ARoleAttLED = (PINB ^= 0b00100000);
int ARoleDefLED = (PINB ^= 0b01000000);
int BRoleAttLED = (PINB ^= 0b10000000);
int BRoleDefLED = (PIND ^= 0b00100000);
int gameRunningLED = (PINB ^= 0b00010000);
int AAttack = (PINB ^= 0b00001000);
int BAttack = (PINB ^= 0b00000100);

int gameRunning;
int attacker;
int defstrike;
int attstrike;
int Apoint;
int Bpoint;
int attack;
int dodge;

void point(void) {
	defstrike = 0;
	attstrike = 0;
	gameRunning = 0;
	if (attacker) {
		Apoint++; 
	} else {
		Bpoint++;
	}
}
void roleswitch(void) {
	defstrike = 0;
	attstrike = 0;
	gameRunning = 0;
	attacker = !attacker;
}

int main(void)
{
    /* Setup phase */
	DDRB = 0b01111101;
	DDRC = 0b00000000;
	DDRD = 0b11100000;
	PORTB = 0b00000000;
	PORTC = 0b00001111;
	PORTD = 0b00001100;
	
	while (1) 
    {
		if(!gameRunning && LeftButtonA && LeftButtonB && RightButtonA && RightButtonB && !AttackButtonA && !AttackButtonB) {
			attack = 0;
			dodge = 0;
			/* Countdown Lights */
			TimerALED;
			_delay_ms(250);
			TimerBLED;
			_delay_ms(250);
			TimerCLED;
			_delay_ms(250);
			TimerALED;
			TimerBLED;
			TimerCLED;
			gameRunning = 1;
			gameRunningLED;
			if (attacker) {
				/* A is Attacker B is Defender*/
				while (gameRunning) {
					if(!(attack)&&!(LeftButtonA&&RightButtonA)) {
						attack = 1;
					}
					if(!(dodge)&&!(LeftButtonB||RightButtonB)) {
						dodge = 1;
					}
					if(dodge&&!attack) {
						defstrike++;
						gameRunning = 0;
					}
					if(attack&&(LeftButtonA&&RightButtonA)) {
						attstrike++;
						gameRunning = 0;
					}
					if(attack&&AttackButtonA&&!dodge){
						point(); 
					}
					if(attack&&AttackButtonA&&dodge){
						roleswitch();
					}
					
				}
			} else {
				/* A is Defender B is Attacker */
				while (gameRunning) {
					if(!(attack)&&!(LeftButtonB&&RightButtonB)) {
						attack = 1;
					}
					if(!(dodge)&&!(LeftButtonA||RightButtonA)) {
						dodge = 1;
					}
					if(dodge&&!attack) {
						defstrike++;
						gameRunning = 0;
					}
					if(attack&&(LeftButtonB&&RightButtonB)) {
						attstrike++;
						gameRunning = 0;
					}
					if(attack&&AttackButtonB&&!dodge){
						point(); 
					}
					if(attack&&AttackButtonB&&!dodge){
						roleswitch();
					}
				}
			}
			if(attstrike>=3) {
				roleswitch();
			}
			if(defstrike>=3) {
				point();
			}
		}
    }
}
