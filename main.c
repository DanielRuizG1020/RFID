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
#include "MFRC522.h"
#include "rfid.h"
#include "oled.h"

// Custom libraries
#define RST_PIN 0// Pin 9 para el reset del RC522
#define SS_PIN  17 // Pin 10 para el SS (SDA) del RC522
#define SPI_PORT 0


uint8_t bufferRead[18]; // Buffer para guardar la lectura
uint8_t bufferWrite[16] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                            0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                            0x01, 0x01, 0x01, 0x01}; // Buffer de escritura

// Main function
int main() {
    // Initialize standard I/O
    stdio_init_all();
    sleep_ms(7000);
    initialize_display_and_render_text();
     // Print initialization message
    printf("Probando RFID\n");
    MFRC522Ptr_t mfrc522 = MFRC522_Init(); // Inicializa el MFRC522
    PCD_Init(mfrc522, SPI_PORT); // Inicializa el puerto SPI

    while(1){
        
        //writeBlock(mfrc522,1,bufferWrite);
        readBlock(mfrc522,1,bufferRead);
        sleep_ms(1000);
    }

    return 0;
}
