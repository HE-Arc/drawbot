#include <Servo.h>
#include <EEPROM.h>
#include <math.h>

// CONSTANTES
const int S1=7, S2=8;               // Sorties arduino S1:bras, S2:avant-bras
const int VITESSE=40;               // Pause en ms après un mouvement
const int MIN_US=550, MAX_US=2350;  // Commande servo en us (tester 700-2300)
const int COR_X=5, COR_Y=12;        // Corrections x,y
double COR_S1=6.8, COR_S2=-3.4;     // Correction angle servos en degrés

// VARIABLES 
Servo s1, s2;             // s1: épaule (en A), s2: coude (en B)
double lg1=149, lg2=130;  // longueur des bras (mm)  lg1 = AB (bras), lg2 = BC (avant-bras)
double angle1, angle2;    // position servos en degrés de s1 et s2
double old1, old2;        // position précédente des angles
double pas = 0.5;         // distance souhaitée en mm entre 2 points
double par = M_PI/180;    // angle en radians entre deux calculs de points (1°)
bool microsec = true;     // Mode précis (0.1°) si true
bool debug = true;        // Affiche les déplacements dans le moniteur série

// FONCTIONS
//void initServos();                  // place les servos en position intiale
//void moveServos();                  // déplace les servos => (x,y)
//bool isInside(double x, double y);  // teste si (x,y) se trouve dans la feuille A4
//bool toAngle(double x, double y);   // cinématique inverse : (x,y) => angles s1 et s2
//
//void droite(double x1, double y1, double x2, double y2);
//void rectangle(double x1, double y1, double x2, double y2);
//void cercle(double xc, double yc, double r);
//void spirale(double xc, double yc, double r, double pas);

void log(char msg[], double t, double x, double y){
    Serial.print(msg);Serial.print(" - t:");Serial.print(t);Serial.print(":(");Serial.print(x);
    Serial.print(","); Serial.print(y);Serial.println(")");
}

void log(double x, double y){
  Serial.print("angles: S1:");Serial.print(angle1);Serial.print(" S2:");Serial.println(angle2);
  Serial.print(" (x,y) : (");Serial.print(x);Serial.print(",");Serial.print(y);Serial.println(")\n");
}

void lectureCorrectif(){

  delay(500);
  int E_MSB = EEPROM.read(0);
  int E_LSB = EEPROM.read(1);
  delay(500);
  int A_MSB = EEPROM.read(2);
  int A_LSB = EEPROM.read(3);
  int epaule  = 256*E_MSB+E_LSB;
  int coude   = 256*A_MSB+A_LSB;

  int etendue = MAX_US-MIN_US;
  int cor_epaule = epaule-1500;        // écarts en us
  int cor_coude = coude-1500; 

  COR_S1 = cor_epaule * 180./etendue;   //écarts en degrés
  COR_S2 = cor_coude * 180./etendue;

  Serial.print("EEPROM:Epaule=");Serial.print(epaule);Serial.print(", Coude=");Serial.print(coude);
  Serial.print(", Cor en us : (");Serial.print(cor_epaule);Serial.print(",");Serial.print(cor_coude);
  Serial.print("), Cor en degrés : (");Serial.print(COR_S1);Serial.print(",");Serial.print(COR_S2); Serial.print(")");
  Serial.println("ok");Serial.println("ok");Serial.println("ok");Serial.println("ok");Serial.println("ok");Serial.println("ok");
  
}

