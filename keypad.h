

#ifndef __KEYPAD_
#define __KEYPAD_
#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 4
#define MAX_LETTERS_PRESSED 5

#include <stdio.h>
#include "pico/stdlib.h"



extern volatile uint8_t aux;
extern volatile bool keyflag;
extern volatile bool password_correct;
extern volatile bool password_finish;


//void keypress(uint8_t aux);
void keypress(uint8_t aux,uint8_t state);
void analyze_letter_input(void);
void timer_sequence_handler(void);
void gpio_callback(uint gpio, uint32_t events);
void setup_keyboard(void);
void analyze_password(void); 




#endif