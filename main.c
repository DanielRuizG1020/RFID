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
#include "main.h"

// Custom libraries
#define RST_PIN 0// Pin 9 para el reset del RC522
#define SS_PIN  17 // Pin 10 para el SS (SDA) del RC522
#define SPI_PORT 0

// Main function
int main() {
    // Initialize standard I/O
    stdio_init_all();
    sleep_ms(7000);
    setup_keyboard();
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
                    keyflag = false;
                    keypress(aux,state);
                    if (password_correct == true && password_finish == true){
                        state++;
                        password_correct = false;
                        password_finish = false;
                    }
                    else if(password_correct == false && password_finish == true) {
                        password_finish = false;
                        password_correct = false;
                        state = 0;
                    }    
                }
                break;

            case 2:
                readBlock(mfrc522, 1, bufferRead);
                delay(2000);
                state++;
                keyflag = false;
            case 3:
                if (keyflag == 1) {
                    keyflag = false;
                    keypress(aux,state);
                    
                } 
                break;   
            // Agrega más casos según sea necesario
            default:
                // Manejo de estado desconocido, si es necesario
                break;
        }

        tight_loop_contents(); // Esto asegura que el bucle sea lo más eficiente posible
    }

    return 0;
}



