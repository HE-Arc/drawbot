/*
 * Programme de réglage pour le robot dessinateur
 * 
 * sauvegarde le zéro des servos dans l'EEPROM
 * 
 * HE-ARC/GHU/nov 2016
 * 
 */
 // TODO
 // afficher valeurs sauvegardées 
 // positionner les bras aux valeur de l'EEPROM au lancement ?
 // utiliser https://www.arduino.cc/en/Reference/Bitshift pour lect/ecriture EEPROM
 
#include <EEPROM.h>
#include <Servo.h>

Servo s1, s2;               // s1: épaule (en A), s2: coude (en B)
int a, b;
int epaule = 1500;
int coude = 1500;
byte MSBepaule, LSBepaule;
byte MSBcoude,  LSBcoude;
bool Flag_epaule = true ; // flag qui indique si on règle l'épaule (true) ou l'avant-bras
int sens = 1 ;            // sens de la correction (déterminé par les touches + et -)

const int delta = 2 ;     // valeur de l'incrément pour le réglage (en microsecondes)
const int S1 = 7;         // Pin servo 1
const int S2 = 8;         // Pin servo 2

void setup() {
  Serial.begin(9600);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  s1.attach(S1, 550, 2350);
  s2.attach(S2, 550, 2350);
  s1.writeMicroseconds(1500);  // servo au centre
  s2.writeMicroseconds(1500);  // servo au centre
  delay(10000);
  Serial.println("bras mis en place");   
  int E_MSB = EEPROM.read(0);
  int E_LSB = EEPROM.read(1);
  int A_MSB = EEPROM.read(2);
  int A_LSB = EEPROM.read(3);
  
  int epaule = 256*E_MSB+E_LSB;
  int coude = 256*A_MSB+A_LSB;
  Serial.print("La position memorisee pour l'epaule est de : "); Serial.println(epaule);
  Serial.print("La position memorisee pour le coude est de : "); Serial.println(coude);
}

void loop() {
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("Reglage des bras du robot ");
  Serial.println("ATTENTION : mettre le moniteur en mode 9600baud et Retour chariot ");
  Serial.println("Entrez une commande au clavier (a valider par ENTER) ");
  Serial.println("           E  : pour entrer dans le mode reglage de l'epaule ");
  Serial.println("           C  : pour entrer dans le mode reglage du coude ");
  Serial.println("                     S  : pour sortir et memoriser le reglage");
  Serial.println("                     +  : pour faire tourner le servo dans le sens positif (anti - horaire)");
  Serial.println("                     -  : pour faire tourner le servo dans le sens negatif (horaire)");

  int entree_clavier = 0;
  while ((entree_clavier != 'E') && (entree_clavier != 'C') && (entree_clavier != 86) ) { // 86=V ????
    entree_clavier = LectureClavier(); // on teste le clavier en attendant E ou C
  }
  if (entree_clavier == 'E') {
    Flag_epaule = true;
  }
  else
  {
    Flag_epaule = false;
  }

  Serial.println("Mode regalge du bras");
  Serial.println("     + pour tourner le bras dans le sens antihoraire");
  Serial.println("     - pour tourner le bras dans le sens horaire");
  while ((entree_clavier != '+') && (entree_clavier != '-') ) {
    entree_clavier = LectureClavier(); // on teste le clavier en attendant + ou -
  }
  if (entree_clavier == '+') {
    sens = 1;
  }
  else
  {
    sens = -1;
  }

  Serial.println("     Entrer pour continuer le reglage");
  Serial.println("     S pour sortir du mode Reglage Epaule");
  while (entree_clavier != 'S') { // à répéter tant que l'on a pas entrer S

    while ((entree_clavier != 13) && (entree_clavier != 'S') ) {
      entree_clavier = LectureClavier(); // on teste le clavier en attendant Enter ou S
    }
    if (Flag_epaule && (entree_clavier == 13))
    { epaule = epaule + sens * delta;
      s1.writeMicroseconds(epaule);
    }
    if (!Flag_epaule && (entree_clavier == 13))
    { coude = coude - sens * delta;
      s2.writeMicroseconds(coude);
    }

    if (entree_clavier == 'S') {
      Serial.println("Attendez un instant : sauvegarde du reglage Epaule");
      if (Flag_epaule)
      {
        MSBepaule = epaule / 256;
        LSBepaule = epaule - MSBepaule * 256;
        EEPROM.write(0, MSBepaule); // MSByte réglage épaule : adresse 0 EEPROM
        EEPROM.write(1, LSBepaule); // LSByte réglage épaule : adresse 1 EEPROM
        delay(3000);   // délai pour attendre la fin de l'écriture sur l'EEPROM
        Serial.println("Le reglage de l epaule est memorise");
      }
      else
      {
        MSBcoude = coude / 256;
        LSBcoude = coude - MSBepaule * 256;
        EEPROM.write(2, MSBcoude); // MSByte réglage avant-bras : adresse 2 EEPROM
        EEPROM.write(3, LSBcoude); // LSByte réglage avant-bras : adresse 3 EEPROM
        delay(3000);   // délai pour attendre la fin de l'écriture sur l'EEPROM
        Serial.println("Le reglage du Coude est memorise");
      }
    }
    else
    {
      Serial.print("La position a ete mise a jour : ");
      Serial.print(" Epaule = ");
      Serial.print(epaule);
      Serial.print(" Avant bras = ");
      Serial.println(coude);
      Serial.println();
      Serial.println("     Entrer pour continuer le reglage");
      Serial.println("     S pour sortir du mode Reglage Epaule");
      entree_clavier = 0;
    }
  }
}

int LectureClavier() {
  a = 0;
  b = 0;
  while (Serial.available() != 0 ) {
    a = Serial.read();
    delay(50);  // délai pour que les caractères arrivent dans le buffer
    b = Serial.read();
    delay(50);  // délai pour que les caractères arrivent dans le buffer

  } // attente d'une entrée au clavier (deux caractères dont un CR dans b)
  if (a>96) a = a - ('a'-'A'); // si c'est une minuscule, on la convertit en majuscule
  return a;
}




