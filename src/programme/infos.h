/* 
  C======B========A
+------------------------------------+
|           Feuille A4               |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
+------------------------------------+
A : Origine (x croissants vers gauche et y vers bas)
A : Position servo s1 (pos=0, AB est orienté à droite pour pos=180)
B : Position servo s2 (pos=180, C proche de A pour pos=0)
C : Position crayon 

 TODO :
 Détailler angles
 Dessin maison doc
 Pos initiale => 1er point du dessin ???
 collision si s2<28?
 interactions avec le clavier ?

TESTER :
 Ralentissement du déplacement si deltaAngle > 3°
 lecture du zero dans eprom
 pos et taille figures
 
 Correctifs origine et angles ->ok
 Limiter déplacement à feuille ->ok
 simplifier droite()->ok
 utiliser writeMicroseconds()->ok
 zone couverte : -148 < x < -148 // 0 < y < 210

*/

while(true) {
  s1.write(0);Serial.println("0");delay(1000);
  s1.write(90);Serial.println("90");delay(1000);
  s2.write(0);Serial.println("0");delay(1000);
  s2.write(90);Serial.println("90");delay(1000);
  s2.write(180);Serial.println("90");delay(1000);
  s2.write(90);Serial.println("90");delay(1000);
  s1.write(180);Serial.println("180");delay(1000);
}

