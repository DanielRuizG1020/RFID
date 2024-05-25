#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include <stdlib.h>
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/timer.h"
#include "pico/time.h"
#include "keypad.h"


volatile bool password_correct = false;
volatile bool password_finish = false;
volatile bool keyflag = false;
volatile bool buy;
volatile bool sell;


const char matrix_keys[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

const uint gpio_rows[] = {2, 3, 4, 5};
const uint gpio_columns[] = {6, 7, 8, 9};
volatile uint8_t sequence = 0;
volatile uint8_t aux =0;

const uint32_t DEBOUNCE_TIME_US = 200000;
//uint64_t last_press_time = 0; ///< Tiempo de la última pulsación del teclado
uint8_t letter_index = 0; ///< Índice para el texto ingresado por el usuario
volatile char current_key = '\0'; ///< Tecla actual presionada en el teclado matricial
char text_input[MAX_LETTERS_PRESSED] = "0000"; ///< Almacena el texto ingresado por el usuario
char password[] = "1234"; ///< Contraseña de 4 dígitos 




void gpio_callback(uint gpio, uint32_t events) {
    keyflag=true;
    aux = gpio;
    gpio_acknowledge_irq(gpio, events);
}


void setup_keyboard(void) {
    for (int i = 0; i < 4; i++) {
        gpio_init(gpio_rows[i]);
        gpio_set_dir(gpio_rows[i], GPIO_OUT);
        gpio_init(gpio_columns[i]);
        gpio_set_dir(gpio_columns[i], GPIO_IN);
        gpio_pull_down(gpio_columns[i]);
        gpio_set_irq_enabled_with_callback(gpio_columns[i], GPIO_IRQ_EDGE_RISE, true, gpio_callback);
    }
}


void timer_sequence_handler(void){
    // Interrupt acknowledge
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_IRQ_0);
     // Setting the IRQ handler
    irq_set_exclusive_handler(TIMER_IRQ_0, timer_sequence_handler);
    irq_set_enabled(TIMER_IRQ_0, true);
    hw_set_bits(&timer_hw->inte, 1u << TIMER_IRQ_0); ///< habilitar la alarma0 para la secuencia
    timer_hw->alarm[0] = (uint32_t)(time_us_64() + 2000); ///< establecer la alarma0 para que se active en 2ms

    //Generacion secuencia 
    uint8_t sq; ///< Valor de secuencia
    sequence = (sequence + 1) % 4; ///< Incrementar la secuencia
    sq = 1 << sequence; ///< Valor de secuencia
    gpio_put_masked(0xF<<gpio_rows[0], ((uint32_t) sq )<< gpio_rows[0]); ///< Establecer la secuencia en las filas  
    
}

 void analyze_letter_input() {
    printf("Escoja un tipo de transaccion\n");
    printf("Texto ingresado: %s\n", text_input);
    if (text_input[0] == 'A') {
        printf("Compra");
        printf( "\n");
        buy = true;
        sell = false;
         
    } else if (text_input[0] == 'B') {
        printf("Venta");
        printf( "\n");
        buy = false;
        sell = true;
    }
    letter_index = 0;
    memset(text_input, 0, sizeof(text_input));   
 }



void analyze_password() {
    if (strncmp(text_input, password, 4) == 0) {
        password_correct = true;
        printf("Contraseña Correcta\n");
    } else {
        password_correct = false;
        printf("Contraseña Incorrecta\n");
    }
    password_finish = true;
    letter_index = 0;
    memset(text_input, 0, sizeof(text_input)); 
}


void keypress(uint8_t aux, uint8_t state) {
    static uint64_t last_press_time = 0;
    if (time_us_64() - last_press_time < DEBOUNCE_TIME_US) {
        return;
    }
    
    for (int col = 0; col < 4; col++) { 
        if (gpio_columns[col] == aux) {
            current_key = matrix_keys[sequence][col];
            text_input[letter_index] = current_key;
            printf("Tecla presionada: %c\n", current_key);
            letter_index = letter_index + 1; 
            if (state == 1) {
                if (letter_index == 4) { 
                    analyze_password();
                }
            } else if (state == 3) {
                if (letter_index == 1) { 
                    analyze_letter_input();
                }
            }
            last_press_time = time_us_64();  
        }
        
    }
}



