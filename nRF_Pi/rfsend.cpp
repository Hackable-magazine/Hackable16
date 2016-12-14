#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <RF24/RF24.h>

RF24 radio(22,0);

const uint64_t pipeA = 0xF0F0F0F0E1LL;
const uint64_t pipeB = 0xF0F0F0F0D2LL;

int main(int argc, char** argv){
  unsigned long message;
  unsigned long debut;
  bool timeout;
  unsigned long reception;
  unsigned long fin;

  printf("Go go go!\n");

  radio.begin();

  // Activer l'accusé réception
  radio.enableAckPayload();
  // L'accusé réception est dynamique
  radio.enableDynamicPayloads();
  // réglage de l'amplificateur
  radio.setPALevel(RF24_PA_LOW);

  // réglage des canaux (pipe)
  radio.openWritingPipe(pipeB);
  radio.openReadingPipe(1,pipeA);

  // affichage d'un résumé de la configuration
  radio.printDetails();

  // En écoute
  radio.startListening();

  while(1) {
     // Arrêt écoute
     radio.stopListening();

     printf("Envoi\n");
     message = millis();

     // Envoi avec vérification d'erreur
     if(!radio.write(&message, sizeof(unsigned long))) {
        printf("Erreur : write.\n");
     }

     // Mise en écoute
     radio.startListening();

     // Enregistrement du début du délai
     debut = millis();
     timeout = false;

     // Tant que rien à lire
     while (!radio.available()) {
        if (millis()-debut > 600) {
	   timeout = true;
	   break;
	}
     }

     // abandon pour cause de délai écoulé ?
     if(timeout){
        printf("Erreur : timeout.\n");
     } else {
        // lecture des données reçues
	radio.read(&reception, sizeof(unsigned long));
	// enregistrement du moment de la réception
	fin = millis();

	// Affichage
	printf("Message: %lu, reponse: %lu, temps complet: %lu\n", message, reception, fin-message);
     }

     // dodo 1 seconde
     sleep(1);
  }
  return 0;
}

