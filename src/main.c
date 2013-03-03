#define F_CPU 80000000
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

// time to wait between button press and tempo output (in timer ticks)
#define TEMPO_SET_TIMEOUT 500

// time to light LED for each beat (in clock cycles)
#define LED_BEAT_TIME     1000

// the initial period of the beats (in timer ticks)
#define INITIAL_PERIOD    100

// the minimum time between button presses for debounce (in timer ticks)
#define DEBOUNCE_TIME     35

// pin mappings
#define BUTTON_PIN  DDB0
#define LED_PIN     DDB4
#define SPEAKER_PIN DDB2

// macros to control LED
#define LED_ON()  PORTB |= _BV(LED_PIN);
#define LED_OFF() PORTB &= ~(_BV(LED_PIN));

// counts timer ticks
volatile unsigned long counter;
// period of current tempo (in timer ticks)
volatile unsigned long period;
// time stamp of counter when button was last presed
volatile long last_press;

// flash the LED for a short period of time to indicate a tick
void led_beat() {
    unsigned long i;
    LED_ON();
    for (i=0; i < LED_BEAT_TIME; i++) {__asm("nop");}
    LED_OFF();
}

// toggle the speaker to indicate a tick
void speaker_beat() {
    PORTB ^= _BV(SPEAKER_PIN);
}

void init(void) {
    // stop the watchdog
    wdt_disable();

    // configure output pins
    PORTB = 0;
    DDRB |= (_BV(LED_PIN) | _BV(SPEAKER_PIN));

    // configure button pin (B0 is an input, interrupt on change)
    // enable pull up
    PORTB |= _BV(BUTTON_PIN);
    GIMSK |= (1 << PCIE);
    PCMSK |= (1 << PCINT0);

    // configure timer
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << CS02) | (1 << CS00) | (1 << CS00);
    OCR0A = 1;
    TIMSK0 |= (1 << OCIE0A);
    sei();

    // set the inital period
    period = INITIAL_PERIOD;
}

int main (void)
{
    init();
    for (;;);
    return 1;
}


// timer interrupt
ISR(TIM0_COMPA_vect) {
    counter++;
    // check if beat period has been hit
    if (counter % period == 0) {
        // only beat if a timeout from last button press has occured
        if ((counter - last_press) > TEMPO_SET_TIMEOUT) {
            led_beat();
            speaker_beat();
        }
    }
}

// button interrupt
ISR(PCINT0_vect) {
    int delta;

    // only trigger on falling edge
    if (PINB & _BV(DDB0)) {return;}

    // display the beat
    led_beat();
    speaker_beat();

    // calculate the time delta in timer ticks
    delta = counter - last_press;

    // ensure delta is > 5 for debouncing
    if (delta > DEBOUNCE_TIME) {
        // set the period in timer ticks to the time between the last two presses
        period = delta;
    }

    // set the last pressed timestamp to the current counter value
    last_press = counter;

    return;
}
