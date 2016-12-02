bool isInside(float x, float y){
  if( x < MIN_X+COR_X ){
    LOG("OUT X", x, "<", MIN_X + COR_X);
    return false;
  }
  if( x > MAX_X+COR_X ){
    LOG("OUT X", x, ">", MAX_X + COR_X);
    return false;
  }
  if( y < MIN_Y+COR_Y ){
    LOG("OUT Y", y, "<", MIN_Y + COR_Y);
    return false;
  }
  if( y > MAX_Y + COR_Y){
    LOG("OUT Y", y, ">", MAX_Y + COR_Y);
    return false;
  }
  return true;
}

bool toAngle(float x, float y){
  // Merci Julien Marchand et François Tièche !!!
  float r, t, alpha, beta, gamma, halfPerimeter, angleR1, angleR2;
  bool lefty = false;   // pas utile avec la config mécanique choisie

  old1 = angle1;
  old2 = angle2;

  // Application correctifs translation
  x+=COR_X;
  y+=COR_Y;

  r = sqrt(x*x + y*y);
  alpha = atan2(y, x);
  halfPerimeter = (lg1+lg2+r) / 2.;

  // sin(beta/2)
  t = (halfPerimeter-lg1)*(halfPerimeter-r)/(lg1*r);
  if (t < 0.0) {
    LOG("INACCESSIBLE\n");
    
    return false;
  }

  beta = asin(sqrt(t))*2.0;

  // sin(gamma/2)
  t = (halfPerimeter-lg1)*(halfPerimeter-lg2)/(lg1*lg2);
  if (t < 0.0) {
     LOG("INACCESSIBLE\n");
     return false;
  }

  gamma = asin(sqrt(t))*2.0;
  gamma -= M_PI;

  angleR1 = alpha + (lefty ? beta : -beta);
  angleR2 = (lefty ? gamma : -gamma);

  if (isInside(x,y)) {
    angle1 = angleR1 * 180 / M_PI;
    angle2 = angleR2 * 180 / M_PI;
    // Application correctifs angles
    angle1 += COR_S1;
    angle2 += COR_S2;

    if (angle2<ANGLE_MIN) {
      // Evite les collisions
      angle2 = ANGLE_MIN;
    }

    LOG(x, y);
    return true;
  }

  LOG("HORS DE LA FEUILLE\n");
  return false;
}

void moveServos()
{
  // Si grande distance ralentir mouvement
/*  float delta =3;
  int inc;
 
  if (abs(angle1-old1)>delta) {
    if (angle1 > old1) {
      for (float i=old1; i<angle1; i+=1) {
        s1.write(i);
        delay(VITESSE);
      }
    }
    else {
      for (float i=angle1; i<old1; i-=1) {
        s1.write(i);
        delay(VITESSE);
      }      
    }
  }

  if (abs(angle2-old2)>delta) {
    if (angle2 > old2) {
      for (float i=old2; i<angle2; i+=1) {
        s2.write(i);
        delay(VITESSE);
      }
    }
    else {
      for (float i=angle2; i<old2; i-=1) {
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
    LOG(".");
  }
  LOG("INIT\n");
}

