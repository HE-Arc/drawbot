## Bras dessinateur

![Prototype du bras](http://www.he-arc.ch/sites/www.he-arc.ch/files/ING/haute-ecole-arc-ingenierie-atelier-robot-dessinateur.jpg "Prototype du bras")

Ce robot peut dessiner des formes simples à partir des mouvements des moteurs situés aux 2 articulations. Les moteurs sont contrôlés par un [arduino][https://www.arduino.cc/]. Le code proposé permet de tracer des droites, des cercles, des spirales et des fonctions mathématiques (formes de coeur ou d'étoile, par exemple...) après avoir converti la position à atteindre en angles qui correspondent à la position des moteurs des articulations.

## Atelier 

Ce projet est conçu pour être monté et pris en main par des enfants à partir de 10 ans dans le cadre d'un atelier.

L'atelier se déroule en 3 phases :

1. Soudage de la carte de contrôle 
2. Assemblage du support (pièces pré-découpées en MDF)
3. Présentation et modification du logiciel pour personnaliser les dessins

## Code 

Dans /src :

* reglages : projet Arduino permettant d'ajuster finement la géométrie des bras
* programme : projet Arduino qui permet d'exécuter un dessin avec le robot
* generateur : projet Qt pour dessiner à la souris et écrire la liste de points qui consitue le dessin dans un fichier texte. Ce fichier texte pourra ensuite être repris dans programme, pour être dessiné par le robot
* simulateur : projet Processing permettant d'afficher le dessin d'un programme sur l'écran avant de le dessiner avec le robot

## Licence

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Licence Creative Commons" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />Cette œuvre est mise à disposition selon les termes de la <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Licence Creative Commons Attribution 4.0 International</a>.

## Crédits

Ont participé au développement du projet : Gérald Huguenin, David Grunenwald, Alexandre Neukomm, Julien Marchand, François Tièche

Avec les moyens mis à disposition par la [HE-Arc Ingénierie](http://www.he-arc.ch/ingenierie) et le [Fablab Neuchâtel](http://fablab-neuch.ch/)