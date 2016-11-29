// Jusqu'à la ligne 130, le code est identique à simulateur/dessins.pde
// https://en.wikipedia.org/wiki/Hypotrochoid
void etoile(float cx, float cy, float r) // étoile à 5 branches
{
  float x,y;
  float r1=r, r2=r*3/5, d=r;
  for (float t = 0; t<6*PI; t+=par) {
    x = cx + (r1-r2)*cos(t) + d*cos((r1-r2)/r2 * t);
    y = cy + (r1-r2)*sin(t) - d*sin((r1-r2)/r2 * t);
    toAngle(x,y);
    moveServos();    
    if (debug) log("HYPO", t, x, y);
  }  
}

void etoile() { etoile(0, 100, 50); }

// https://en.wikipedia.org/wiki/Epicycloid
void fleur(float cx, float cy, float rTotal, float k) // rosace
{
  float rCircleOut=rTotal/(k+1.0);
  float rCircleIn=rCircleOut*k;
  float x,y;
  for (float t = 0; t<2*PI; t+=par) {
    x = cx+(rCircleIn + rCircleOut)*cos(t) - rCircleOut*cos((rCircleIn/rCircleOut + 1)* t);
    y = cy + (rCircleIn + rCircleOut)*sin(t) - rCircleOut*sin((rCircleIn/rCircleOut + 1)*t);
    toAngle(x,y);
    moveServos();    
    if (debug) log("EPI", t, x, y);
  }  
}

void fleur() { fleur(0, 130, 40, 3); }

// Coeur de Raphaël Laporte
// http://www.les-mathematiques.net/phorum/read.php?8,418124,418399
void coeur(float cx, float cy, float r)
{
  float x,y;
  float taille=50;
  cy=cy+2.0*r*1.5/5.0;
  for (float t = 0; t<2*PI; t+=par) {
    x = cx + r*(sin(t)*sin(t)*sin(t));
    y = cy + r*cos(t) - r*(cos(t)*cos(t)*cos(t)*cos(t));
    toAngle(x,y);
    moveServos();    
    if (debug) log("COEUR", t, x, y);
  }
}

void coeur() { coeur(0, 130, 40); }

void cercle(float cx, float cy, float r)
{
  float x,y;
  for (float t = 0; t<2*PI; t+=par) {
    x = r * cos(t) + cx; 
    y = r * sin(t) + cy;
    toAngle(x,y);
    moveServos();    
    if (debug) log("CERCLE", t, x, y);
  }
}

void cercle() {cercle(0, 100, 30);}

void spirale(float cx, float cy, float cr, float pas) 
{
  float x,y, ppd = pas/360; // pas par degré

  while (cr>3) {
    for(int t=0; t<360; t++){
      x = cr * cos(t *(PI/180)) + cx; 
      y = cr * sin(t *(PI/180)) + cy;
      toAngle(x,y);
      moveServos();
      cr-=ppd;
      if (cr<1) break;
    if (debug) log("SPIRALE", t, x, y);
    }
  }
}

void spirale() { spirale(0, 100, 50, 5); }

void droite(float x1, float y1, float x2, float y2){
  float distance = sqrt(sq(x2-x1)+sq(y2-y1));
  float step = pas;    // d en mm
  int nbPoints = (int)(1 + distance/step);    
  float dx=(x2-x1)/nbPoints; 
  float dy=(y2-y1)/nbPoints;
  float x=x1, y=y1;
  
  for (int i=0; i<nbPoints; i++){
    toAngle(x,y);
    moveServos();   
    x = x + dx;
    y = y + dy;     
    if (debug) log("DROITE", i, x, y);
  }  
}

void rectangle(float x1, float y1, float x2, float y2){
  droite(x1, y1, x2, y1);
  droite(x2, y1, x2, y2);
  droite(x2, y2, x1, y2);
  droite(x1, y2, x1, y1);
}

void maison(float x, float y, float h){
  float w=h*2/3.0;
  float xLeft=x-w/2.0;
  float xRight=x+w/2.0;
  float yTopRoof=y+h/2.0;
  float yTopWall=y+h/6.0;
  float yBottom=y-h/2.0;
  
  droite(xLeft,yBottom,xLeft,yTopWall);
  droite(xLeft,yTopWall,xRight,yBottom);
  droite(xRight,yBottom,xRight,yTopWall);
  droite(xRight,yTopWall, xLeft,yTopWall);
  droite(xLeft,yTopWall,x,yTopRoof);
  droite(x,yTopRoof,xRight,yTopWall);
  droite(xRight, yTopWall,xLeft,yBottom);
  droite(xLeft,yBottom,xRight,yBottom);
}

void maison() {maison(0, 100, 50);}

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
    if (debug) log("LISTE", 0, x, y);
  }
}

void mire(){
  float x,y;
  float cx=0, cy=lg1-20, r=lg2;
  // arc
  for (float t = -PI/8; t<PI/8; t+=par) {
    x = r * cos(t) + cx; 
    y = r * sin(t) + cy;
    toAngle(x,y);
    moveServos();    
    if (debug) log("CALIBRAGE", t, x, y);
  }
  // retour et segment
  
}

