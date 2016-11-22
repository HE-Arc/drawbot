// https://en.wikipedia.org/wiki/Hypotrochoid
void hypotrochoide(double cx=0, double cy=100, double r=50) // étoile à 5 branches
{
  double x,y;
  double r1=r, r2=r*3/5, d=r;
  for (double t = 0; t<6*M_PI; t+=par) {
    x = cx + (r1-r2)*cos(t) + d*cos((r1-r2)/r2 * t);
    y = cy + (r1-r2)*sin(t) - d*sin((r1-r2)/r2 * t);
    toAngle(x,y);
    moveServos();    
    if (debug) log("HYPO", t, x, y);
  }  
}

// https://en.wikipedia.org/wiki/Epicycloid
void epicycloide(double cx=0, double cy=130, double a=16, double b=10) // rosace
{
  double x,y;
  for (double t = 0; t<2*M_PI; t+=par) {
    x = (a + b)*cos(t) - b*cos((a/b + 1)* t);
    y = 130 + (a + b)*sin(t) - b*sin((a/b + 1)*t);
    toAngle(x,y);
    moveServos();    
    if (debug) log("EPI", t, x, y);
  }  
}

// Coeur de Raphaël Laporte
// http://www.les-mathematiques.net/phorum/read.php?8,418124,418399
void coeur(double cx=0, double cy=130, double r=40)
{
  double x,y;
  double taille=50;
  for (double t = 0; t<2*M_PI; t+=par) {
    x = cx + r*(sin(t)*sin(t)*sin(t));
    y = cy + r*cos(t) - r*(cos(t)*cos(t)*cos(t)*cos(t));
    toAngle(x,y);
    moveServos();    
    if (debug) log("COEUR", t, x, y);
  }
}

void cercle(double cx=0, double cy=100, double r=30){
  double x,y;
  for (double t = 0; t<2*M_PI; t+=par) {
    x = r * cos(t) + cx; 
    y = r * sin(t) + cy;
    toAngle(x,y);
    moveServos();    
    if (debug) log("CERCLE", t, x, y);
  }
}

void spirale(double cx=0, double cy=100, double cr=50, double pas=5) {
  double x,y, ppd = pas/360; // pas par degré

  while (cr>3) {
    for(int t=0; t<360; t++){
      x = cr * cos(t *(M_PI/180)) + cx; 
      y = cr * sin(t *(M_PI/180)) + cy;
      toAngle(x,y);
      moveServos();
      cr-=ppd;
      if (cr<1) break;
    if (debug) log("SPIRALE", t, x, y);
    }
  }
}

void droite(double x1, double y1, double x2, double y2){
  double distance = sqrt(sq(x2-x1)+sq(y2-y1));
  double step = pas;    // d en mm
  int nbPoints = 1 + distance/step;
  double dx=(x2-x1)/nbPoints; 
  double dy=(y2-y1)/nbPoints;
  double x=x1, y=y1;
  
  for (int i=0; i<nbPoints; i++){
    toAngle(x,y);
    moveServos();   
    x = x + dx;
    y = y + dy;     
    if (debug) log("DROITE", i, x, y);
  }  
}

void rectangle(double x1, double y1, double x2, double y2){
  droite(x1, y1, x2, y1);
  droite(x2, y1, x2, y2);
  droite(x2, y2, x1, y2);
  droite(x1, y2, x1, y1);
}

void maison(){
  droite(-75,90,-75,140);
  droite(-75,140,-25,90);
  droite(-25,90,-25,140);
  droite(-25,140, -75,140);
  droite(-75,140,-50,190);
  droite(-50,190,-25,140);
  droite(-25, 140,-75,90);
  droite(-75,90,-25,90);
  droite(-25,90,-75,90);
}

void mire(){
  double x,y;
  double cx=0, cy=lg1-20, r=lg2;
  for (double t = -M_PI/8; t<M_PI/8; t+=par) {
    x = r * cos(t) + cx; 
    y = r * sin(t) + cy;
    toAngle(x,y);
    moveServos();    
    if (debug) log("CALIBRAGE", t, x, y);
  }
}

