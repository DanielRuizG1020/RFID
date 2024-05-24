/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */

// Standard libraries
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "MFRC522.h"
#include "rfid.h"
#include "oled.h"
#include "keypad.h"

// Custom libraries
#define RST_PIN 0// Pin 9 para el reset del RC522
#define SS_PIN  17 // Pin 10 para el SS (SDA) del RC522
#define SPI_PORT 0
uint8_t state=0;
uint8_t bufferRead[18]; // Buffer para guardar la lectura
uint8_t bufferWrite[16] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                            0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                            0x01, 0x01, 0x01, 0x01}; // Buffer de escritura

// Main function
int main() {
    // Initialize standard I/O
    stdio_init_all();
    sleep_ms(7000);
    setup_keyboard();
    bool id_target;
    timer_sequence_handler();
    timer_display_handler();
    //initialize_display_and_render_text();
     // Print initialization message
    printf("Probando RFID\n");
    MFRC522Ptr_t mfrc522 = MFRC522_Init(); // Inicializa el MFRC522
    PCD_Init(mfrc522, SPI_PORT);

    while (1) {
        switch (state) {
            case 0:
                id_target= read_card_id(mfrc522);
                //readBlock(mfrc522, 1, bufferRead);
                if (id_target == true){
                    state++;
                }
                keyflag = false;
                break;
            case 1:
                if (keyflag == 1) {
                    keypress(aux);
                    keyflag = false;
                    if (password_correct == true && password_finish == true){
                        state++;
                        keyflag = false;
                    }
                    else if(password_correct == false && password_finish == true) {
                        keyflag = false;
                        password_finish = false;
                        password_correct = false;
                        state = 0;
                    }
                    
                }
                break;

            case 2:
                printf("cambio de estado");
            // Agrega más casos según sea necesario
            default:
                // Manejo de estado desconocido, si es necesario
                break;
        }

        tight_loop_contents(); // Esto asegura que el bucle sea lo más eficiente posible
    }

    return 0;
}



void timer_display_handler(void){
    // Interrupt acknowledge
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_IRQ_1);
     // Setting the IRQ handler
    irq_set_exclusive_handler(TIMER_IRQ_1, timer_display_handler);
    irq_set_enabled(TIMER_IRQ_1, true);
    hw_set_bits(&timer_hw->inte, 1u << TIMER_IRQ_1); ///< habilitar la alarma0 para la secuencia
    if(state != 2){
    timer_hw->alarm[1] = (uint32_t)(time_us_64() + 1000000);
    initialize_display_and_render_text();  ///< establecer la alarma0 para que se active en 2ms
    }
    else{
        update_display("Secuencia 1", "Secuencia 2", "Secuencia 3", "Secuencia 4");
    }
      
}