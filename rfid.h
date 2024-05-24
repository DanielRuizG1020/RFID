#ifndef __RFID_
#define __RFID_


// Write your definitions and other macros here
/**brief: Funcion que lee un bloque de la tarjeta
 * 
 * @param mfrc: Puntero a la estructura MFRC522
 * @param block: Bloque a leer
 * @param bufferRead: Buffer donde se guardara la informacion leida
 * 
 * @return void
 */
void readBlock(MFRC522Ptr_t mfrc,uint8_t block,uint8_t bufferRead[18]);

/**brief: Funcion que escribe un bloque de la tarjeta
 * 
 * @param mfrc: Puntero a la estructura MFRC522
 * @param block: Bloque a escribir
 * @param bufferWrite: Buffer con la informacion a escribir
 * 
 * @return void
 */
void writeBlock(MFRC522Ptr_t mfrc, uint8_t block, uint8_t bufferWrite[16]);
bool compareUIDs(const uint8_t *uid, size_t uidLength, const uint8_t *expectedUID, size_t expectedUIDLength);
bool read_card_id(MFRC522Ptr_t mfrc);

#endif