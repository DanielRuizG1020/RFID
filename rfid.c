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
#include "RFID.h"

MIFARE_Key keyBlock = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void readBlock(MFRC522Ptr_t mfrc,uint8_t block,uint8_t bufferRead[18]){
    uint8_t len=18;
    printf("Coloque la tarjeta\n\r");
    while(!PICC_IsNewCardPresent(mfrc));
    printf("Leyendo\n\r");
    PICC_ReadCardSerial(mfrc);
    printf("Reconocida\n\r");
    if(PCD_Authenticate(mfrc,PICC_CMD_MF_AUTH_KEY_A,block,&keyBlock, &(mfrc->uid))==0){
        printf("Authentication Sabrosa\n\r");
        if(MIFARE_Read(mfrc,block,bufferRead,&len)==0){
            printf("leida bloque Sabroso\n\r");
           for (int i = 0; i < 16; i++) {
                printf("%u ", bufferRead[i]);
            }
           PCD_StopCrypto1(mfrc);
           printf( "\n");
        }else{
        printf("Leida de bloque failed: \n\r");
        }
    }else{
        printf("Authentication failed: \n\r");
}
}


void writeBlock(MFRC522Ptr_t mfrc, uint8_t block, uint8_t bufferWrite[16]) {
    uint8_t len = 16;
    printf("Coloque la tarjeta\n\r");
    while (!PICC_IsNewCardPresent(mfrc));
    printf("Escribiendo\n\r");
    PICC_ReadCardSerial(mfrc);
    printf("Reconocida\n\r");
    if (PCD_Authenticate(mfrc, PICC_CMD_MF_AUTH_KEY_A, block, &keyBlock, &(mfrc->uid)) == 0) {
        printf("Autenticación Sabrosa\n\r");
        if (MIFARE_Write(mfrc, block, bufferWrite, len) == 0) {
            printf("Bloque escrito Sabroso\n\r");
            PCD_StopCrypto1(mfrc);
        } else {
            printf("Error al escribir el bloque\n\r");
        }
    } else {
        printf("Error en la autenticación\n\r");
    }
}                            