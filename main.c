/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "MFRC522.h"
#include "rfid.h"
#include "oled.h"
#include "keypad.h"
#include "main.h"
#define RST_PIN 0   // Pin 9 para el reset del RC522
#define SS_PIN  17 // Pin 10 para el SS (SDA) del RC522
#define SPI_PORT 0


int main() {

    stdio_init_all();
    sleep_ms(7000);
    setup_keyboard();
    timer_sequence_handler();
    timer_display_handler();
    printf("Probando RFID\n");
    MFRC522Ptr_t mfrc522 = MFRC522_Init();
    PCD_Init(mfrc522, SPI_PORT);

    while (1) {
        switch (state) {
            case 0:
                id_target= read_card_id(mfrc522);
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
                delay(3000);
                state++;
                keyflag = false;
            case 3:
                if (keyflag == 1) {
                    keyflag = false;
                    keypress(aux,state);
                    if (buy == true && sell == false){
                        switch (bufferRead[0])
                        {
                        case 0: 
                            apple.units_available = bufferRead[1];
                            apple.sell_price = bufferRead[2];
                            apple.buy_price = bufferRead[3];
                            inventory[0] = inventory[0] + apple.units_available;
                            inventory[6] = inventory[6] - ((apple.buy_price)*(apple.units_available));
                            printf("Cash:  %u", inventory[6]);
                            printf( "\n");
                            printf("Apple units:  %u", inventory[0]);
                            printf( "\n");
                            break;
                        case 1:
                            banana.units_available = bufferRead[1];
                            banana.sell_price = bufferRead[2];
                            banana.buy_price = bufferRead[3];
                            inventory[1] = inventory[1] + banana.units_available;
                            inventory[6] = inventory[6] - ((banana.buy_price)*(banana.units_available));
                            printf("Cash:  %u", inventory[6]);
                            printf( "\n");
                            printf("Banana units:  %u", inventory[1]);
                            printf( "\n");
                            break;
                        case 2: 
                            pineapple.units_available = bufferRead[1];
                            pineapple.sell_price = bufferRead[2];
                            pineapple.buy_price = bufferRead[3];
                            inventory[2] = inventory[2] + pineapple.units_available;
                            inventory[6] = inventory[6] - ((pineapple.buy_price)*(pineapple.units_available));
                            printf("Cash:  %u", inventory[6]);
                            printf( "\n");
                            printf("Pineapple units:  %u", inventory[2]);
                            printf( "\n");
                            break;
                        case 3:
                            cherry.units_available = bufferRead[1];
                            cherry.sell_price = bufferRead[2];
                            cherry.buy_price = bufferRead[3];
                            inventory[3] = inventory[3] + cherry.units_available;
                            inventory[6] = inventory[6] - ((cherry.buy_price)*(cherry.units_available));
                            printf("Cash:  %u", inventory[6]);
                            printf( "\n");
                            printf("Cherry units:  %u", inventory[3]);
                            printf( "\n");
                            break;
                        case 4:
                            grape.units_available = bufferRead[1];
                            grape.sell_price = bufferRead[2];
                            grape.buy_price = bufferRead[3];
                            inventory[4] = inventory[4] + grape.units_available;
                            inventory[6] = inventory[6] - ((grape.buy_price)*(grape.units_available));
                            printf("Cash:  %u", inventory[6]);
                            printf( "\n");
                            printf("Grape units:  %u", inventory[4]);
                            printf( "\n");
                            break;                     
                        default: 
                            printf("Solo se manejan 5 productos");
                            state = 0;
                            break;
                        }
                        buy = false;
                        sell = false;
                        state = 0;       
                    }
                    
                    else if(buy == false && sell == true) {
                        switch (bufferRead[0]) {

                        case 0:
                            apple.units_available = bufferRead[1];
                            apple.sell_price = bufferRead[2];
                            apple.buy_price = bufferRead[3];
                            inventory[0] = inventory[0] - apple.units_available;
                            inventory[5]= inventory[5] + ((apple.sell_price)*(apple.units_available));
                            printf("Sales:  %u", inventory[5]);
                            printf( "\n");
                            printf("Apple units: %u", inventory[0]);
                            printf( "\n");
                            break;
                        case 1:
                            banana.units_available = bufferRead[1];
                            banana.sell_price = bufferRead[2];
                            banana.buy_price = bufferRead[3];
                            inventory[0] = inventory[0] - banana.units_available;
                            inventory[5]= inventory[5] + ((banana.sell_price)*(banana.units_available));
                            printf("Sales:  %u", inventory[5]);
                            printf( "\n");
                            printf("Banana units: %u", inventory[1]);
                            printf( "\n");
                        case 2:
                            pineapple.units_available = bufferRead[1];
                            pineapple.sell_price = bufferRead[2];
                            pineapple.buy_price = bufferRead[3];
                            inventory[0] = inventory[0] - pineapple.units_available;
                            inventory[5]= inventory[5] + ((pineapple.sell_price)*(pineapple.units_available));
                            printf("Sales:  %u", inventory[5]);
                            printf( "\n");
                            printf("Pineapple units: %u", inventory[0]);
                            printf( "\n");
                            break;
                        case 3:
                            cherry.units_available = bufferRead[1];
                            cherry.sell_price = bufferRead[2];
                            cherry.buy_price = bufferRead[3];
                            inventory[0] = inventory[0] - cherry.units_available;
                            inventory[5]= inventory[5] + ((cherry.sell_price)*(cherry.units_available));
                            printf("Sales:  %u", inventory[5]);
                            printf( "\n");
                            printf("Cherry units: %u", inventory[0]);
                            printf( "\n");
                            break;
                        case 4:
                            grape.units_available = bufferRead[1];
                            grape.sell_price = bufferRead[2];
                            grape.buy_price = bufferRead[3];
                            inventory[0] = inventory[0] - grape.units_available;
                            inventory[5]= inventory[5] + ((grape.sell_price)*(grape.units_available));
                            printf("Sales:  %u", inventory[5]);
                            printf( "\n");
                            printf("Grape units: %u", inventory[0]);
                            printf( "\n");
                            break;
                    
                        default:
                            printf("Producto Inexistente");
                            state = 0;
                            break;
                        }
                        buy = false;
                        sell = false;
                        state = 0; 
                    }
                    break;
                }   
              
            default:
                
                break;
        }

        tight_loop_contents(); 
    }

    return 0;
}



