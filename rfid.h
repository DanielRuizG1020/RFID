#ifndef __RFID_
#define __RFID_


// Write your definitions and other macros here
/**
 * @brief: Funcion que lee un bloque de la tarjeta
 * 
 * @param mfrc: Puntero a la estructura MFRC522
 * @param block: Bloque a leer
 * @param bufferRead: Buffer donde se guardara la informacion leida
 * 
 * @return void
 */
void readBlock(MFRC522Ptr_t mfrc,uint8_t block,uint8_t bufferRead[18]);

/**
 * @brief: Funcion que escribe un bloque de la tarjeta
 * 
 * @param mfrc: Puntero a la estructura MFRC522
 * @param block: Bloque a escribir
 * @param bufferWrite: Buffer con la informacion a escribir
 * 
 * @return void
 */

void writeBlock(MFRC522Ptr_t mfrc, uint8_t block, uint8_t bufferWrite[16]);
/**
 * @brief Compara dos UID (Identificadores Únicos) para determinar si son iguales.
 * 
 * Esta función compara un UID leído de una tarjeta RFID con un UID esperado.
 * Retorna verdadero si ambos UID son iguales en longitud y contenido.
 * 
 * @param uid Puntero al array que contiene el UID leído.
 * @param uidLength Longitud del UID leído.
 * @param expectedUID Puntero al array que contiene el UID esperado.
 * @param expectedUIDLength Longitud del UID esperado.
 * 
 * @return true Si los UID son iguales en longitud y contenido.
 * @return false Si los UID no son iguales en longitud o contenido.
 */

bool compareUIDs(const uint8_t *uid, size_t uidLength, const uint8_t *expectedUID, size_t expectedUIDLength);
/**
 * @brief Lee el UID de una tarjeta RFID y verifica si coincide con un UID esperado.
 * 
 * Esta función espera hasta que una nueva tarjeta esté presente, lee el UID de la tarjeta
 * y lo compara con un UID esperado para determinar si coincide.
 * 
 * @param mfrc Puntero a la estructura MFRC522 que contiene la información y métodos para interactuar con el lector RFID.
 * 
 * @return true Si el UID leído coincide con el UID esperado.
 * @return false Si el UID leído no coincide con el UID esperado.
 */
bool read_card_id(MFRC522Ptr_t mfrc);

#endif