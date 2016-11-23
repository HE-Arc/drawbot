#include "declarations.h"
#include "cinematique.h"
#include "dessins.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  s1.attach(S1, MIN_US, MAX_US);    // place le servo à 90° (pas toujours...)
  s2.attach(S2, MIN_US, MAX_US);
  delay(100);
}

void loop() {
  Serial.println("Loop");
  lectureCorrectif();

  spirale(-100, 170, 25);
  cercle(-30, 170, 25);
  fleur(40, 170, 25);
  coeur(-100, 100, 25);
  hypotrochoide(-30, 100, 25);
  maison(-100, 35, 50);
  //double delta=0.0;
  //rectangle(MIN_X+delta, MIN_Y+delta, MAX_X-delta, MAX_Y-delta);
  
//  cercle(50, 120, 20);
//  hypotrochoide(0,100,50);
//  epicycloide(0,130,16,10);
//  coeur(0,100,50);

  Serial.println("End \n");
  exit(0);
}

