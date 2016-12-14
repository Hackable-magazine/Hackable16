#include <SPI.h>
#include <SdFat.h>

SdFat sd;

#define SDCS 10
#define BUFFER_SIZE 100
uint8_t buf[BUFFER_SIZE];

void setup() {
  SdFile fichier;
  Serial.begin(115200);

  Serial.println("Initialisation SD...");
  if (!sd.begin(SDCS,SPI_HALF_SPEED)) {
    Serial.println("Erreur initialisation");
    return;
  }

  // Listage de la racine
  sd.ls("/", LS_SIZE|LS_R);

  // Ouverture du fichier
  if (!fichier.open(&sd, "essai.txt", O_RDWR | O_CREAT | O_AT_END )) {
    Serial.println("Erreur ouverture fichier");
    return;
  }

  fichier.println("Coucou ! ceci est un test.");
  fichier.sync();

  /// Fermeture du fichier
  fichier.close(); 

  // Listage de la racine
  Serial.println(" ");
  sd.ls("/", LS_SIZE|LS_R|LS_DATE);
}

void loop() {}
