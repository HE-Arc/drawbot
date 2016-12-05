
boolean debug = false;

int dy=60;
float xmm, ymm, xold, yold;
float par = PI/180*1;    // angle en radians entre deux calculs de points (1°)
float pas = 0.5;         // distance souhaitée en mm entre 2 points
float lg1 = 149, lg2 = 130;  // longueur des bras (mm)  lg1 = AB (bras), lg2 = BC (avant-bras)
float zoom = 4;

void setup() {
  // Callback pour les appels C++ à moveServos et toAngle.
  shared.getCaller().setCallback(new Callback(){
    @Override
    public void moveServos() {
      line(xold, yold, xmm, ymm);
      xold=xmm; yold=ymm;
      if (debug) log("m", 0, xmm, ymm);
    }
    @Override
    public void toAngle(float x, float y) {
      xold=xmm; yold=ymm;
      xmm=x*zoom; ymm=y*zoom;
    }
  });
//  size(pgWidth, pgHeight, PDF, "simulation.pdf");
  background(255);
  stroke(0);
  size(400, 400);
  surface.setResizable(true);
  surface.setSize(int(297*zoom),int(210*zoom));
  noLoop();
}

void draw() {  
  translate(width/2, height);
  scale(1, -1);

  dessineListe();

  //spirale(-100, 170, 25, 5);
  //cercle(-30, 170, 25);
  //fleur(40, 170, 25, 7);
  //coeur(-100, 100, 25);
  shared.etoile(-100, 100, 25);
  etoile(-30, 100, 25);
  //maison(-100, 35, 50);
}

boolean toAngle(float x, float y) {
  xold=xmm; yold=ymm;
  xmm=x*zoom; ymm=y*zoom;

  return true;
}

void moveServos() {
  line(xold, yold, xmm, ymm);
  xold=xmm; yold=ymm;
  if (debug) log("m", 0, xmm, ymm);
}

void log (String text, float t, float x, float y) {
  String msg = text + " // t:" + t + " x=" + x + " y=" + y;
  println(msg);
}