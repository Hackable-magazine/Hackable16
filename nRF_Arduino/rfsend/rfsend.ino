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
  radio.openWritingPipe(pipeB);
  radio.openReadingPipe(1,pipeA);
  
  // En écoute
  radio.startListening();
}

void loop() {
  // Arrêt écoute
  radio.stopListening();
  Serial.println(F("Envoi"));

  // Utilisation de micro comme messahe
  unsigned long message = micros();
  // envoi
  if (!radio.write(&message, sizeof(unsigned long) )){
    Serial.println(F("erreur"));
  }
  
  // Mise en écoute
  radio.startListening();

  // Enregistrement du début du délai
  unsigned long debut = micros();
  boolean timeout = false;

  // Tant que rien à lire
  while (!radio.available()){
    // 600ms de passé, on abandonne
    if (micros()-debut > 600000 ){
      timeout = true;
      break;
    }      
  }

  // abandons pour cause de délai écoulé ?
  if(timeout){
    Serial.println(F("Erreur : timeout."));
  } else {
    // variable pour le message reçu
    unsigned long reception;
    // lecture des données reçues
    radio.read(&reception, sizeof(unsigned long));
    // enregistrement du moment de la réception
    unsigned long fin = micros();

    // Affichage
    Serial.print(F("Message: "));
    Serial.print(message);
    Serial.print(F(", reponse: "));
    Serial.print(reception);
    Serial.print(F(", temps complet: "));
    Serial.print(fin-message);
    Serial.println(F(" microsecondes"));
  }

  delay(1000);

}

