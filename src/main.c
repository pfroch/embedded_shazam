#include <avr/io.h>
#include <util/delay.h>

void adc_init(void) {
    ADMUX = (1 << REFS0);
    
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t read_adc(void) {
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

int main(void) {
    DDRD |= (1 << PD6) | (1 << PD7);
    DDRB |= (1 << PB0);

    adc_init();

    while (1) {
        uint16_t val = read_adc();

        //low -> PD6
        if (val > 550 || val < 450) {
            PORTD |= (1 << PD6);
        } else {
            PORTD &= ~(1 << PD6);
        }

        //mid -> PD7
        if (val > 650 || val < 350) {
            PORTD |= (1 << PD7);
        } else {
            PORTD &= ~(1 << PD7);
        }

        //high -> PD8
        if (val > 750 || val < 250) {
            PORTB |= (1 << PB0);
        } else {
            PORTB &= ~(1 << PB0);
        }

        _delay_ms(30);
    }

    return 0;
}