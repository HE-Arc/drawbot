
bool isInside(double x, double y){
  if ( (x>-148)&&(x<148)&&(y>0)&&(y<210) ) return true;
  else return false;
}

bool toAngle(double x, double y){
  // Merci Julien Marchand et François Tièche !!!
  double r, t, alpha, beta, gamma,  halfPerimeter, angleR1, angleR2;
  bool lefty = false;   // pas utile avec la config mécanique choisie

  old1 = angle1;
  old2 = angle2;

  x+=COR_X;y+=COR_Y;    // Application correctifs translation

  r = sqrt(x*x+y*y);  
  alpha = atan2(y, x);
  halfPerimeter = (lg1+lg2+r)/2;

  // sin(beta/2)
  t = (halfPerimeter-lg1)*(halfPerimeter-r)/(lg1*r);
  if (t < 0.0) {
    Serial.println("INACESSIBLE");
    return false;
  }

  beta = asin(sqrt(t))*2.0;

  // sin(gamma/2)
  t = (halfPerimeter-lg1)*(halfPerimeter-lg2)/(lg1*lg2);
  if (t < 0.0) {
     Serial.println("INACCESSIBLE");
     return false;
  }

  gamma = asin(sqrt(t))*2.0;
  gamma -= M_PI;

  angleR1 = alpha + (lefty ? beta : -beta);
  angleR2 = (lefty ? gamma : -gamma);

  if (isInside(x,y)) {
    angle1 = angleR1 * 180 / M_PI;
    angle2 = angleR2 * 180 / M_PI;
    angle1+=COR_S1;angle2+=COR_S2;            // Application correctifs angles
    if (angle2<ANGLE_MIN) angle2 = ANGLE_MIN; // Evite les collisionsq
  }
  else {
      Serial.println("HORS DE LA FEUILLE");
      return false;
  }
  if (debug) log(x,y);
  return true;
}

void moveServos()
{
  // Si grande distance ralentir mouvement
/*  double delta =3;
  int inc;
 
  if (abs(angle1-old1)>delta) {
    if (angle1 > old1) {
      for (double i=old1; i<angle1; i+=1) {
        s1.write(i);
        delay(VITESSE);
      }
    }
    else {
      for (double i=angle1; i<old1; i-=1) {
        s1.write(i);
        delay(VITESSE);
      }      
    }
  }

  if (abs(angle2-old2)>delta) {
    if (angle2 > old2) {
      for (double i=old2; i<angle2; i+=1) {
        s2.write(i);
        delay(VITESSE);
      }
    }
    else {
      for (double i=angle2; i<old2; i-=1) {
        s2.write(i);
        delay(VITESSE);
      }      
    }
  }
  */
  if (microsec) {
    int us1, us2;
    int precision=100; // à cause du casting en long dans map()
                       // granularité 0.1° du servo ((2000-1000)/180)
    us1 = map (angle1*precision, 0, 180*precision, MIN_US, MAX_US);
    us2 = map ((180-angle2)*precision, 0, 180*precision, MIN_US, MAX_US);
  
    s1.writeMicroseconds(us1);
    s2.writeMicroseconds(us2);
  }
  else {
    s1.write(COR_S1+angle1+.5);       // +.5 : arrondit au lieu de tronquer
    s2.write(180-(COR_S2+angle2)-.5);   // Servo monté à l'envers    
  }
  delay(VITESSE);
}

void initServos()
{
  angle1=90+COR_S1;
  angle2=90+COR_S2;

  for (int i=0;i<10; i++){
 //   moveServos();
    s1.write(angle1);
    s2.write(angle2);
    delay(20);
    if (debug) Serial.print(".");
  }
  if (debug) Serial.println("INIT");
}

