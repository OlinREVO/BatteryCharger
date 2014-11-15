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
