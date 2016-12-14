#include <SPI.h>
#include <RF24.h>

#define PIN_CS  10
#define PIN_CE  9

RF24 radio(PIN_CE,PIN_CS);

const uint64_t pipeA = 0xF0F0F0F0E1LL;
const uint64_t pipeB = 0xF0F0F0F0D2LL;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Go go go!"));
  
  radio.begin();

  // Activer l'accusé réception
  radio.enableAckPayload();
  // L'accusé réception est dynamique
  radio.enableDynamicPayloads();

  // réglage de l'amplificateur
  radio.setPALevel(RF24_PA_LOW);
  //radio.setPALevel(RF24_PA_HIGH);
  
  // réglage des canaux (pipe)
  radio.openWritingPipe(pipeA);
  radio.openReadingPipe(1,pipeB);
  
  // En écoute
  radio.startListening();
}

void loop() {
  unsigned long temps;

  // Des données sont-elle disponibles ?
  if(radio.available()){
    // oui, lecture
    while (radio.available()) {
      radio.read(&temps, sizeof(unsigned long));
    }

    // arrête émission
    radio.stopListening();
    // envoi de la réponse
    radio.write(&temps, sizeof(unsigned long));
    // reprise de la réception
    radio.startListening();

    // Affichage
    Serial.print(F("pong !  "));
    Serial.println(temps);  
  }
}

