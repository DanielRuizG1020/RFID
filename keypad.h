

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
extern volatile bool buy;
extern volatile bool sell;

/**
 * @brief Maneja la pulsación de una tecla en el teclado matricial.
 *
 * Esta función se encarga de manejar la pulsación de una tecla en el teclado matricial,
 * asegurando un tiempo de debounce adecuado y procesando la tecla según el estado actual.
 *
 * @param aux El valor del GPIO correspondiente a la tecla presionada.
 * @param state El estado actual de la máquina de estados.
 */
void keypress(uint8_t aux,uint8_t state);

/**
 * @brief Analiza la entrada de letras y determina el tipo de transacción.
 *
 * Esta función imprime un mensaje para solicitar al usuario que seleccione un tipo de transacción.
 * Luego, analiza la entrada de letras proporcionada por el usuario y determina si se ha seleccionado
 * una compra o una venta. Finalmente, reinicia el índice de letras y limpia el arreglo de texto de entrada.
 */
void analyze_letter_input(void);

/**
 * @brief Manejador del temporizador para la secuencia.
 *
 * Esta función maneja la generación de la secuencia y la actualización de la alarma del temporizador.
 * Cuando se activa la interrupción del temporizador, esta función se ejecuta para actualizar la secuencia y
 * establecer la próxima alarma del temporizador.
 */
void timer_sequence_handler(void);

/**
 * @brief Función de devolución de llamada del GPIO.
 *
 * Esta función se llama cuando se detecta una interrupción en el GPIO.
 * Establece la bandera keyflag en verdadero para indicar que se ha presionado una tecla.
 * Registra el GPIO y los eventos y luego reconoce la interrupción del GPIO.
 *
 * @param gpio   El número de GPIO que generó la interrupción.
 * @param events Los eventos asociados con la interrupción del GPIO.
 */
void gpio_callback(uint gpio, uint32_t events);

/**
 * @brief Configuración del teclado.
 *
 * Esta función configura los pines del teclado, inicializa los pines de fila como salida
 * y los pines de columna como entrada con resistencia de pull-down.
 * Además, habilita las interrupciones de los pines de columna con la función de devolución de llamada del GPIO.
 */
void setup_keyboard(void);

/**
 * @brief Análisis de la contraseña ingresada.
 *
 * Esta función compara la contraseña ingresada con la contraseña esperada.
 * Si la contraseña ingresada coincide con la contraseña esperada, establece la bandera
 * `password_correct` en verdadero y muestra un mensaje de "Contraseña Correcta".
 * De lo contrario, establece `password_correct` en falso y muestra un mensaje de "Contraseña Incorrecta".
 * También marca la finalización de la entrada de la contraseña, reinicia el índice de letras y
 * borra el arreglo de texto `text_input`.
 */
void analyze_password(void); 


#endif