import processing.pdf.*;
// A1 = (1684,2384);
// A2 = (1191,1684);
// A3 = (842,1191);
// A4 = (595,842);

int pgWidth=842, 
    pgHeight=595;
    
int dy=60;

void setup() {
  size(pgWidth, pgHeight, PDF, "calibrage.pdf");
  background(255);
  //strokeCap(SQUARE);  // Commenter pour arrondi
}


void arc(){
  
  float xc = map (147, 0, 297, 0, pgWidth);
  float yc = map (80, 0, 210, 0, pgHeight);
  float dx = map (260, 0, 297, 0, pgWidth);
  float dy = map (260, 0, 210, 0, pgHeight);
  float fromX = map (268, 0, 297, 0, pgWidth);
  float toX = map (288, 0, 297, 0, pgWidth);

  ellipseMode(CENTER);
  arc(xc, yc, dx, dy, -PI/8, PI/8);
  line(fromX, yc, toX, yc);
  
//   line(10, 10, 50, 10);
}


void segment(){
}




void note(int haut, int debut, int fin, int epais)
/*
0 < haut < 7
0 < debut, fin < 297
0 < epais < 10
*/
{
  stroke(0);
  float nEpais= map(epais,     0, 10,   0, 29); 
  float nDebut= map(debut,     0, 297,  0, pgWidth);
  float nFin  = map(fin,       0, 297,  0, pgWidth);
  float nHaut = map(haut*10+15+dy, 0, 210,  0, pgHeight);

  strokeWeight(nEpais);
  line (nDebut, nHaut, nFin, nHaut);
}

void draw() {
  arc();
//  portee();
//
//  PImage logo = loadImage("../tskz.jpg");
//  image(logo, 640, 480);
//  
//  textSize(12);
//  fill(0);
//  text("Calibrage du phonolux : led en haut, bouton B1", 20, 30);
//  text("1. Calibrage blancs : B1", 20,150, 150, 20);
//  text("2. Calibrage noirs : B1", 180,150, 150, 20);
//  text("3. Dessine ta partition avec un feutre de 3mm", 380,150,500, 20);
//  text("4. Change le timbre : B2",20,470);
//  text("5. Change la gamme : B3",20,495);
//// Calibrage 
//  for (int i=-1; i<9; i++)
//    note(i,  85, 95, 2);
//  
//  strokeWeight(.001);
//  stroke(100);
//  
//   float x=map(60, 0, 297, 0, pgWidth);
//   float y=map(65,0,210,0,pgHeight);
//   float y2=map(65+90,0,210,0,pgHeight);
//
//   line (x, y, x, y2);
//
//   x=map(120, 0, 297, 0, pgWidth);
//   line (x, y, x, y2);
//
//  println("Partition Générée");
  exit();
}

void portee(){
  float h;

  // Portées
  strokeWeight(.001);
  stroke(100);
  for (int i=-1; i<9; i++) {
    h=map(i*10+15+dy,0,210,0,pgHeight);
    line (0, h, width, h);
  }

}
