#define F_CPU (1000000L)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define ADC_CHANNEL (0)

int main (void) {
    //Enable ADC, set prescalar to 128 (slow down ADC clock)
    ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    //Enable internal reference voltage
    ADCSRB &= _BV(AREFEN);
    //Set internal reference voltage as AVcc
    ADMUX |= _BV(REFS0);
    //ADC0 is PE2. Set as input pin
    DDRE &= ~(_BV(PE2));

    //No prescaling on PWM clock
    TCCR0B |= (1 << CS00);
    //Set up phase-correct PWM on OC0B
    TCCR0A |= (1 << COM0B1) | _BV(WGM00);
    TCCR0A &= ~(1 << COM0B0);
    DDRE |= ( 1 << PE1 ); //set OC0B as output.

    for (;;) {
        //Reset ADC Channel
        ADMUX &= ~(0x1F);
        ADMUX |= ADC_CHANNEL;

        //Get ADC reading
        ADCSRA |= _BV(ADSC);
        while(bit_is_set(ADCSRA, ADSC)) {}

        uint16_t current = ADC;
    }
    return 1;
}
