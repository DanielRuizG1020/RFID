/**
 * @file main.h
 * @brief This is a brief description of the main H file.
 *
 * Detailed description of the main C file.
 */
 
// Avoid duplication in code
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "MFRC522.h"
#include "rfid.h"
#include "oled.h"
#include "keypad.h"

bool id_target;
uint8_t num1 = 1;
uint8_t num2 = 0;
uint8_t num3 = 0;
uint8_t num4 = 1;
uint8_t state=0;
uint8_t bufferRead[18]; // Buffer para guardar la lectura
uint8_t bufferWrite[16] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                            0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                            0x01, 0x01, 0x01, 0x01}; // Buffer de escritura




void timer_display_handler(void){
    // Interrupt acknowledge
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_IRQ_1);
     // Setting the IRQ handler
    irq_set_exclusive_handler(TIMER_IRQ_1, timer_display_handler);
    irq_set_enabled(TIMER_IRQ_1, true);
    hw_set_bits(&timer_hw->inte, 1u << TIMER_IRQ_1); ///< habilitar la alarma0 para la secuencia
    if(state != 2){
    timer_hw->alarm[1] = (uint32_t)(time_us_64() + 2000000);
    show_current_inventory(num1,num2,num3,num4);  ///< establecer la alarma0 para que se active en 2ms
    }
    else{
        timer_hw->alarm[1] = (uint32_t)(time_us_64() + 2000000);
        show_current_inventory(bufferRead[0],bufferRead[1],bufferRead[2],bufferRead[3]);
    }
      
}

void delay(uint32_t milliseconds) {
    uint64_t start_time = time_us_64();

    // Convertir el tiempo de espera de milisegundos a microsegundos
    uint64_t delay_us = (uint64_t) milliseconds * 1000;

    while ((time_us_64() - start_time) < delay_us) {
        // Esperar hasta que haya pasado el tiempo especificado
    }
}


#endif