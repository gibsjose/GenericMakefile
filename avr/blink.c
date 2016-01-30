#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>

#define F_CPU 8000000UL     //8MHz clock speed
#define F_OSC F_CPU

#define LED_PIN PB5         //PB5 is the Arduino LED pin
#define LED_DD  DDB2        //LED pin Data Direction

#define TIMER1_COUNT    ((FOSC / 1024) - 1)     //Timer 1 count value for CTC mode: 1 second, at 1024 prescaler

//Timer 1 Compare Interrupt Vector (1s CTC Timer)
ISR(TIMER1_COMPA_vect) {
	//Blink LED
	PORTB ^= _BV(LED_PIN);
}

//Timer 1 Initialization
int timer1_init(void) {
	//Initialize Timer 1
	TCCR1A = 0;
	TCCR1B = 0;

	//Set CTC compare value (1 second)
	OCR1A = TIMER1_COUNT;

	//Enable CTC mode
	TCCR1B |= (1 << WGM12);

	//Enable 1024 prescaler
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);

	//Enable Timer 1 output compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	return 0;
}

//Main
int main(void) {
    //Clear interrupts
    cli();

    //Initialize LED Port
    DDRB |= _BV(LED_DD);

    //Initialize Timer peripheral
    timer1_init();

    //Enable interrupts
    sei();

    //Infinite Loop
    while(true);
}
