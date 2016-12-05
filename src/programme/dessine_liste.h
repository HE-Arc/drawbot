// Le code qui suit est propre à dessins.h
void dessineListe() {
  int max = sizeof(liste)/sizeof(int);
  float x,y;

  // tableau de points dans la mémoire programme
  //  https://www.arduino.cc/en/Reference/PROGMEM
  x = (int)pgm_read_word(liste)/100;
  y = (int)pgm_read_word(liste+1)/100;
  toAngle(x, y);
  for (int i=0; i<max-1; i+=2) {
    x = (int)pgm_read_word(liste+i)/100;
    y = (int)pgm_read_word(liste+i+1/100);
    toAngle(x, y);
    moveServos();
    LOG("LISTE", 0, x, y);
  }
}
