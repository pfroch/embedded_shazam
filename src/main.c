#include <avr/io.h>
#include <util/delay.h>
#include "fix_fft.h"

#define FFT_N 64
#define SAMPLE_DELAY_US 125

void adc_init(void) {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t read_adc(void) {
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));//wait
    return ADC;
}

int main(void) {
    DDRD |= (1 << PD6) | (1 << PD7);
    DDRB |= (1 << PB0);

    adc_init();

    int8_t real_buffer[FFT_N];
    int8_t imag_buffer[FFT_N];

    while (1) {
        for (uint8_t i = 0; i < FFT_N; i++) {
            uint16_t raw_val = read_adc();
            
            real_buffer[i] = (int8_t)((raw_val >> 2) - 128);
            imag_buffer[i] = 0;

            _delay_us(SAMPLE_DELAY_US);
        }

        fix_fft(real_buffer, imag_buffer, 6, 0);

        int8_t low_val  = real_buffer[3];
        int8_t mid_val  = real_buffer[12];
        int8_t high_val = real_buffer[25];

        int8_t low_mag  = (low_val < 0) ? -low_val : low_val;
        int8_t mid_mag  = (mid_val < 0) ? -mid_val : mid_val;
        int8_t high_mag = (high_val < 0) ? -high_val : high_val;

        if (low_mag > 35) {
            PORTD |= (1 << PD6);
        } else {
            PORTD &= ~(1 << PD6);
        }

        if (mid_mag > 25) {
            PORTD |= (1 << PD7);
        } else {
            PORTD &= ~(1 << PD7);
        }

        if (high_mag > 20) {
            PORTB |= (1 << PB0);
        } else {
            PORTB &= ~(1 << PB0);
        }
        _delay_ms(30);
    }

    return 0;
}