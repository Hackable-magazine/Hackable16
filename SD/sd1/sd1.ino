#include <SPI.h>
#include <SdFat.h>

#define SDCS 10

// objet sd
SdFat sd;

void setup() {
  uint32_t taille;
  cid_t cid;
  
  Serial.begin(115200);

  // indispensable initialisation
  Serial.println("Initialisation SD...");
  if (!sd.cardBegin(SDCS,SPI_HALF_SPEED)) {
    Serial.println("Erreur initialisation");
    return;
  }

  // Type de carte
  Serial.print("\nType de carte: ");
  switch (sd.card()->type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Inconnu");
  }

  // obtention de la taille de la carte
  taille = sd.card()->cardSize();
  if(!taille) {
    Serial.println("Erreur taille");
    return;        
  }
  Serial.print("Taille physique: ");
  Serial.print((taille*512)/1024/1024);
  Serial.println(" Mo");

  // obtention des informations
  if (!sd.card()->readCID(&cid)) {
    Serial.println("Erreur readCID");
    return;
  }

  // affichage des information
  Serial.print("Fabricant ID: ");
  Serial.println(int(cid.mid), HEX);
  
  Serial.print("OEM ID: ");
  Serial.print(cid.oid[0]);
  Serial.println(cid.oid[1]);
  
  Serial.print("Produit: ");
  for (uint8_t i = 0; i < 5; i++) {
    Serial.print(cid.pnm[i]);
  }
  Serial.println("");
  
  Serial.print("Version: ");
  Serial.print(int(cid.prv_n));
  Serial.print(".");
  Serial.println(int(cid.prv_m));
  
  Serial.print("Numero de serie: ");
  Serial.println(cid.psn,HEX);
  
  Serial.print("Date de fabrication: ");
  Serial.print(int(cid.mdt_month));
  Serial.print("/");
  Serial.println(2000 + cid.mdt_year_low + 10 * cid.mdt_year_high);
}

void loop() {
}
