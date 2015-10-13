/*
   ----------------------------------------------------------------------------
   This is a MFRC522 library example; see https://github.com/miguelbalboa/rfid
   for further details and other examples.

   NOTE: The library file MFRC522.h has a lot of useful info. Please read it.

   Released into the public domain.
   ----------------------------------------------------------------------------
   Example sketch/program which will try the most used default keys listed in
   https://code.google.com/p/mfcuk/wiki/MifareClassicDefaultKeys to dump the
   block 0 of a MIFARE RFID card using a RFID-RC522 reader.

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// Number of known default keys (hard-coded)
// NOTE: Synchronize the NR_KNOWN_KEYS define with the defaultKeys[] array
#define NR_KNOWN_KEYS   8
// Known keys, see: https://code.google.com/p/mfcuk/wiki/MifareClassicDefaultKeys
byte knownKeys[NR_KNOWN_KEYS][MFRC522::MF_KEY_SIZE] =  {
  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // FF FF FF FF FF FF = factory default
  {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5}, // A0 A1 A2 A3 A4 A5
  {0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5}, // B0 B1 B2 B3 B4 B5
  {0x4d, 0x3a, 0x99, 0xc3, 0x51, 0xdd}, // 4D 3A 99 C3 51 DD
  {0x1a, 0x98, 0x2c, 0x7e, 0x45, 0x9a}, // 1A 98 2C 7E 45 9A
  {0xd3, 0xf7, 0xd3, 0xf7, 0xd3, 0xf7}, // D3 F7 D3 F7 D3 F7
  {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}, // AA BB CC DD EE FF
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // 00 00 00 00 00 00
};

byte goodCard[10] = {0x1f, 0xc4, 0x2e, 0x00};
byte goodCard2[10] = {0xcd, 0x37, 0x33, 0x3b};
boolean alarm = false;
const int pinLed = 8;
uint8_t ledStatus;
boolean isLogged = true;
boolean isLastNewCard = false;

/*
   Initialize.
*/
void setup() {
  Serial.begin(115200);         // Initialize serial communications with the PC
  while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();                // Init SPI bus
  mfrc522.PCD_Init();         // Init MFRC522 card
  pinMode(pinLed, OUTPUT);
}

/*
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


void blinkLed() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(pinLed, HIGH);
    delay(500);
    digitalWrite(pinLed, LOW);
    delay(500);
  }
}

/*
   Try using the PICC (the tag/card) with the given key to access block 0.
   On success, it will show the key details, and dump the block data on Serial.

   @return true when the given key worked, false otherwise.
*/
boolean try_key(MFRC522::MIFARE_Key *key)
{
  boolean result = false;
  byte buffer[18];
  byte block = 0;
  byte status;

  // Serial.println(F("Authenticating using key A..."));
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    // Serial.print(F("PCD_Authenticate() failed: "));
    // Serial.println(mfrc522.GetStatusCodeName(status));
    return false;
  }

  // Read block
  byte byteCount = sizeof(buffer);
  status = mfrc522.MIFARE_Read(block, buffer, &byteCount);
  if (status != MFRC522::STATUS_OK) {
    // Serial.print(F("MIFARE_Read() failed: "));
    // Serial.println(mfrc522.GetStatusCodeName(status));
  }
  else {
    // Successful read
    result = true;
    Serial.print(F("Success with key:"));
    dump_byte_array((*key).keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();
    // Dump block data
    Serial.print(F("Block ")); Serial.print(block); Serial.print(F(":"));
    dump_byte_array(buffer, 16);
    Serial.println();
  }
  Serial.println();


  mfrc522.PICC_HaltA();       // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  return result;
}

/*
   Main loop.
*/
void loop() {

  delay(150);

  boolean isNewCard = mfrc522.PICC_IsNewCardPresent();

                      // Look for new cards
  if ( ! isNewCard) {
    if (isLogged && !isNewCard && !isLastNewCard) {
      Serial.write('o');
      isLogged = false;
      delay(3000);
    }
    isLastNewCard = isNewCard;
    return;
  } else {
    isLastNewCard = isNewCard;
  }


  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  } else {
  }

  // Show some details of the PICC (that is: the tag/card)
  //Serial.print(F("Card UID:"));
  //dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  if ((memcmp(goodCard, mfrc522.uid.uidByte, mfrc522.uid.size) == 0 )
      || (memcmp(goodCard2, mfrc522.uid.uidByte, mfrc522.uid.size) == 0))
  {
    if (!isLogged) {
      Serial.write('i');
      isLogged = true;
      delay(3000);
    }
  }
  else
  {
    Serial.write('b');
    delay(3000);
  }


}

