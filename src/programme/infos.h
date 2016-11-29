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
 Détailler angles pour calcul ciné inverse dans doc ?
 Pos initiale => 1er point du dessin ???
 interactions avec le clavier ?
 Terminer mire : dessin segment et retour
 eviter positionnement avec attach (program.ino:9-10)
 incliner bras -40° pour augmenter couverture
 
TESTER :
 Ralentissement du déplacement si deltaAngle > 3° (décommenter cinematique.h:60-92)
 
OK: 
 lecture du zero dans eprom
 pos et taille figures
 taille max d'une liste de points ? => 5700 pts x int x int (22'800 bytes / 30720 progmem)
 determiner valeur min S2 pour éviter collision entre les 2 bras => protéger dans toAngle()
 Correctifs origine et angles ->ok
 Limiter déplacement à feuille ->ok
 simplifier droite()->ok
 utiliser writeMicroseconds()->ok
 zone couverte : -148 < x < -148 // 0 < y < 210

PLUS D'IDEES DE DESSINS :
https://en.wikipedia.org/wiki/Butterfly_curve_(transcendental) 
http://mathworld.wolfram.com/EightCurve.html
http://mathworld.wolfram.com/DumbbellCurve.html
http://mathworld.wolfram.com/PiriformCurve.html
http://rouxjeanbernard.ch/AM/html/amch57.html (spirographe)
http://www.mathcurve.com/courbes2d/ornementales/ornementales.shtml

http://www.gralon.net/actualites/buzz/buzz-dessiner-d-un-seul-trait-138.htm
http://www.huffpostmaghreb.com/2016/02/22/robot-google-photo-dessin-portrait_n_9291590.html

CONTACTS RELATIFS AU PROJET :
gerald.huguenin@he-arc.ch et david.grunenwald@he-arc.ch
https://github.com/HE-Arc/drawbot

*/


// Pour tester les servos
while(true) {
  s1.write(0);Serial.println("0");delay(1000);
  s1.write(90);Serial.println("90");delay(1000);
  s2.write(0);Serial.println("0");delay(1000);
  s2.write(90);Serial.println("90");delay(1000);
  s2.write(180);Serial.println("90");delay(1000);
  s2.write(90);Serial.println("90");delay(1000);
  s1.write(180);Serial.println("180");delay(1000);
}

