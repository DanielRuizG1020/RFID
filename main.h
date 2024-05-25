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
uint8_t inventory[7] = {0,0,0,0,0,0,100};

typedef struct{
    uint8_t name;
    uint8_t units_available;
    uint8_t sell_price;
    uint8_t buy_price;
}product;

product apple =     {0,0,10,5};
product banana =    {1,0,4,2};
product pineapple = {2,0,6,3};
product cherry =    {3,0,8,4};
product grape =     {4,0,9,1};


/**
 * @brief Maneja las interrupciones del temporizador para actualizar la pantalla OLED.
 *
 * Esta función se encarga de manejar las interrupciones del temporizador, actualizar 
 * la pantalla OLED con la información del inventario o del producto actual dependiendo 
 * del estado del sistema, y reprogramar la próxima alarma del temporizador.
 * 
 * @param void
 * 
 * @return void
 */
void timer_display_handler(void){
    // Interrupt acknowledge
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_IRQ_1);
     // Setting the IRQ handler
    irq_set_exclusive_handler(TIMER_IRQ_1, timer_display_handler);
    irq_set_enabled(TIMER_IRQ_1, true);
    hw_set_bits(&timer_hw->inte, 1u << TIMER_IRQ_1); ///< habilitar la alarma0 para la secuencia
    if(state != 2){
        timer_hw->alarm[1] = (uint32_t)(time_us_64() + 2000000);
        show_current_inventory(inventory[0],inventory[1],inventory[2],inventory[3], inventory[4], inventory[5], inventory[6]);  ///< establecer la alarma0 para que se active en 2ms
    }
    else{
        timer_hw->alarm[1] = (uint32_t)(time_us_64() + 2000000);
        show_current_product(bufferRead[0],bufferRead[1],bufferRead[2],bufferRead[3]);
    }
      
}

/**
 * @brief Realiza una espera activa durante un periodo de tiempo especificado en milisegundos.
 *
 * Esta función realiza una espera activa (busy-wait) durante el tiempo especificado. 
 * Utiliza el contador de microsegundos del sistema para realizar la espera.
 *
 * @param milliseconds El tiempo de espera en milisegundos.
 * 
 * @return void
 */
void delay(uint32_t milliseconds) {
    uint64_t start_time = time_us_64();

    // Convertir el tiempo de espera de milisegundos a microsegundos
    uint64_t delay_us = (uint64_t) milliseconds * 1000;

    while ((time_us_64() - start_time) < delay_us) {
        // Esperar hasta que haya pasado el tiempo especificado
    }
}


#endif