import processing.pdf.*;
// A1 = (1684,2384);
// A2 = (1191,1684);
// A3 = (842,1191);
// A4 = (595,842); // Correspond à 210 x 297 mm

int pgWidth=842, 
    pgHeight=595;
    
int dy=60;

void setup() {
  size(842, 595, PDF, "calibrage.pdf");
  background(255);
  //strokeCap(SQUARE);  // Commenter pour arrondi
}

void mire(){
  int lg1 = 149, lg2=130;  // longueurs bras comme dans declarations.h  
  int midX=297/2, arcX = midX-lg2;
  // Calcul des coordonnées processing (origine en haut à gauche, y vers le bas)
  // A partir des valeurs en mm
  float xc = map (midX, 0, 297, 0, pgWidth);
  float yc = map (210-lg1, 0, 210, 0, pgHeight);
  float dx = map (2*lg2, 0, 297, 0, pgWidth);
  float dy = map (2*lg2, 0, 210, 0, pgHeight);
  float fromX = map (arcX-10, 0, 297, 0, pgWidth);
  float toX = map (arcX+10, 0, 297, 0, pgWidth);

  //dessin mire
  ellipseMode(CENTER);
  arc(xc, yc, dx, dy, 7*PI/8, 9*PI/8);
  line(fromX, yc, toX, yc);
  
  // axes
  
  // quadrillage pour aligner le bras
  
  // zone inaccessible
  fill(255,0,0);
  xc = map (midX+lg1, 0, 297, 0, pgWidth);
  yc = map (230, 0, 210, 0, pgHeight); // 210 + décalage axe/feuille
  dx = map (2*lg2, 0, 297, 0, pgWidth);
  dy = map (2*lg2, 0, 210, 0, pgHeight);
  arc(xc, yc, dx, dy, 0, PI);
  
  // textes
  textSize(32);
  fill(0);
  text("-", 20, 120);
  text("+", 20, 240);
  // images
  PImage logo = loadImage("./ArcIng.png");
  image(logo, 520, 540, 300, 50);
}


void draw() {
  mire();
  exit();
}