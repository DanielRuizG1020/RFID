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
#define TIMEOUT_US 1000000

MIFARE_Key keyBlock = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const uint8_t expectedUID[] = {0xCB, 0xE7, 0x27, 0x79};
const size_t expectedUIDLength = sizeof(expectedUID) / sizeof(expectedUID[0]);

void readBlock(MFRC522Ptr_t mfrc,uint8_t block,uint8_t bufferRead[18]){
    uint8_t len=18;
    printf("Coloque la tarjeta\n\r");
    while (!PICC_IsNewCardPresent(mfrc));
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


bool compareUIDs(const uint8_t *uid, size_t uidLength, const uint8_t *expectedUID, size_t expectedUIDLength) {
    if (uidLength != expectedUIDLength) {
        return false;
    }

    for (size_t i = 0; i < uidLength; i++) {
        if (uid[i] != expectedUID[i]) {
            return false;
        }
    }

    return true;
}


bool read_card_id(MFRC522Ptr_t mfrc) {
    printf("Probando id\n\r");
    while (!PICC_IsNewCardPresent(mfrc));
    PICC_ReadCardSerial(mfrc);
    printf("Card UID: ");
    for (uint8_t i = 0; i < mfrc->uid.size; i++) {
        printf("%02X", mfrc->uid.uidByte[i]);
        if (i < mfrc->uid.size - 1) {
            printf(":");
        }
    }
    printf("\n");
    bool isExpectedUID = compareUIDs(mfrc->uid.uidByte, mfrc->uid.size, expectedUID, expectedUIDLength);
    if (isExpectedUID) {
        printf("UID correcto\n\r");
    } else {
        printf("UID incorrecto\n\r");
    }
    PCD_StopCrypto1(mfrc); // Stop encryption on PCD
    return isExpectedUID;
}



