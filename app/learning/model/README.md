# Modèles
## Modèle physique
### Explications sur le modèle physique qui aurait pu être utilisé pour l'asservissement du cube.

moment_to_stay_up = CUBE_MASS \* GRAVITY_CONST \* LEVER_ARM_LENGTH \* sinf(angle)

moment_to_go_to_speed = angular_speed_error \* INERTIA_MOMENT / ASSER_TIME
avec
angular_speed_error = K_SPEED \* angle_error - agular_speed_mesured

moment_total = moment_to_stay_up + moment_to_go_to_speed

current = moment_total / MOTOR_CONSTANT

### Problèmes de ce modèle
Maintenant qu'on a le courant, on veut calculer la tension à appliquer aux moteurs.

On pourrait pour ça réaliser un asservissement proportionel tout simple, mais on a matériellement pas ce qu'il faut pour bien mesurer le courant.
(On mesure très mal les faibles courants, et on ne sais pas mesurer les courants induits par inertie de la roue);

On pourrait mesurer la vitesse angulaire de la roue pour en deduire la force contre electromotrice du moteur, mais on n'a materiellement pas ce qu'il faut pour mesurer la vitesse angulaire de la roue.

Il n'y a pas de modèle physique qui permette de relier directement le courant consommé par le moteur à la tension appliquée.

## Modèle mathématique
### Explications sur le modèle mathématique utilisé pour l'asservissement du cube.
On va donc utiliser un modèle mathématique pour approximer directement la tension en fonction de l'angle et de la vitesse angulaire.
La logique : Aucune.
Le principe : On fait des fonctions (presque) au hasard avec plein de constantes inconnues.
Pleins de parties du modèle sont inutiles (et donc leurs constantes seront = 0), mais ça on en a rien à faire.
Les maths ou la physique ? Connais pas.

tension = a \* (sinf(b\*angle+c))^(-3) + d \* (sinf(b\*angle+c))^(-2) + g \* sinf(b\*angle+c) + h \* (sinf(b\*angle+c))^2 + i \* (sinf(b\*angle+c))^3 + j \* angular_speed^2 + k \* angular_speed + l\*last_tension^(-3) + m\*last_tension^(-2) + n\*last_tension + o\*last_tension^2 + p\*last_tension^3 + q

### Limites de ce modèle
Ce modèle est physiquement incohérent, et ne permet pas de comprendre le comportement du système.
De plus il est très difficile de trouver les bonnes constantes pour que le modèle fonctionne correctement.

### Solutions
Il est donc nécessaire de faire un apprentissage par renforcement pour trouver les bonnes constantes (ou plutôt les moins mauvaises).
Par contre on ne comprendra toujours pas la logique derrière les constantes trouvées.
