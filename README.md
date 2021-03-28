#Programmation II (SV)

###README du groupe 72 (Camille Delgrange, Linda Delacombaz) 

************************************************************************

###A. Présentation du programme:

Notre programme permet de simuler des souris dans des boîtes d'un laboratoire.
Notre laboratoire contient des boîtes, dans lesquelles une souris vit et 
meurt. 
Elle peut se nourrir de fromages, et avoir différents comportements en 
fonction de son état.

Nous pouvons basculer entre deux vues principales: la vue LAB, qui simule 
le laboratoire et la vue ORGANE, qui permet de voir l'évolution d'un organe 
d'une souris.

###Vue Laboratoire

**Comportements d'une souris**

Il existe, dans notre programme, 3 comportements pour une souris:

* Mode "FOOD IN SIGHT"

Par exemple, si la souris a un taux d'énergie trop bas, et qu'il y a un 
fromage à proximité, elle va chercher du fromage dans son rayon de vision
et si elle en trouve dans son champ de vision, elle va aller vers le fromage.

* Mode "FEEDING"

Une fois que la souris à trouvé son fromage, elle se met en mode "FEEDING",
elle se nourrit du fromage et donc augmente son niveau d'énergie. (Et par 
conséquent diminue "l'énergie" du fromage.)

* Mode "WANDERING"

Si la souris a un taux d'énergie assez suffisant, elle n'a "plus besoin"
de se nourrir et donc va simplement se balader dans la boîte, même si il 
y a un fromage dans son champ de vision.

Ces trois modes peuvent être observés en temps réel dans un mode "debug".

(Voir: Fonctionnalités du laboratoire)

**Taux d'énergie d'une souris**

Une souris a son propre niveau d'énergie. Dans notre simulation, nous 
modélisons la "vieillesse" d'une souris: plus le temps passe, plus une 
souris va perdre de l'énergie naturellement.
Si, au bout d'un certain temps, elle n'a plus assez d'énergie, elle meurt
et disparait de notre simulation en "disparaissant" de la boîte automatiquement.

************************************************************************

###Vue Organe

**L'organe d'une souris**

Notre programme modélise également l'organe d'une souris. 
Pour se faire, nous pouvons cibler une souris et regarder l'état de son foie, ainsi que
son réseau sanguin.
Nous avons, dans ce mode de vue: 

-le réseau sanguin de la souris (artère et capillaires sanguin)

-le foie de la souris
Le but du réseau sanguin est de diffuser des substances à travers les
capillaires pour irriguer le foie.
Le foie peut absorber ces substances qui proviennent du réseau sanguin, et 
c'est grâce à ces dernières que les les cellules du foie peuvent se diviser 
continuellement.

Notre foie, tout comme la souris, vieilli et perd constamment de l'énergie.

L'énergie puisée par le foie est modélisée, comme dans la réalité, par 
deux cycles: le cycle de la glycolyse et le cycle de Krebs.

**Diffusion de trois substances**

1. Du glucose, qui est utilisé dans le cycle de la glycolyse et le cycle
de Krebs.
2. Du bromopyruvate, qui est utilisé dans le cycle de la glycolyse, et donc 
joue un rôle d'inhibitueur(voir ci-dessous: Les cellules cancéreuses).
3. Du vgef, mais dans notre programme cela n'a aucune incidence sur notre 
simulation.

Nous pouvons voir les substances diffusées en temps réel en ayant une
troisième vue: la vue concentration. (Voir: les fonctionnalités de l'organe)

Si nous sommes dans ce mode, nous pouvons voir en temps réel la diffusion
des ces substances sur notre réseau sanguin, et l'absoption de ces dernières
par notre foie.

**Les cellules cancéreuses**

Nous pouvons, lorsque nous sommes dans la vue "organe" de la souris, insérer
des cellules cancéreuses, qui peuvent également puiser de l'énergie par les 
substances qui sont diffusées par le réseau sanguin. Ces cellules cancéreuses
peuvent donc se diviser et s'étendre sur nos cellules de foie saines.

Un moyen de combattre ce cancer est d'augmenter le taux de Bromopyruvate
diffusé, car les cellules cancéreuses n'auront plus assez d'énergie
pour se multiplier et donc notre foie pourra se régénérer.


###B. Compilation du programme:

Pour compiler et exécuter le programme principal (FinalApplication),
il faut lancer la commande ci-dessous:
"scons application-run --cfg=fichierdeconfiguration.json", depuis le
répertoire contenant le Sconscript.

###C. Utilisation du programme:


Pour le programme général, lancer avec app.json. (Ou alors, si l'on veut
un rendu encore plus rapide, lancer avec appSmall.json).

**Fonctionnalités du laboratoire:**

Nous pouvons placer le curseur de notre souris notre laboratoire dans une boîte
, et en appuyant sur certaines touches, nous pouvons créer des souris et/ou du 
fromage:

* Touche "M" du clavier : ajout de souris dans une des boîtes. On ne peut
pas ajouter plus d'une souris par boîte.

* Touche "F" du clavier : ajout d'un fromage dans une des boîtes. On peut
ajouter autant de fromages que l'on veut dans une boîte.

* Touche "T" du clavier : "tracker" une souris. Lorsque l'on veut cibler 
une souris pour voir son organe, il faut placer son curseur sur une souris 
de notre choix et appuyer sur la touche "T". Une petite cible violette
devrait alors apparaître sur la souris. On peut tracker qu'une seule souris
à la fois.

* Touche "O" du clavier : Une fois la souris de notre choix traquée,
nous pouvons afficher son organe. Il suffit alors d'appuyer sur la touche
"O" de notre clavier.

* Touche "Z" du clavier : Si l'on veut arrêter de cibler une souris, il
suffit d'appuyer sur la touche Z de notre clavier. Le petit curseur rose 
devrait alors disparaître.

* Touche "R" du clavier: Si l'on veut reset notre laboratoire et "repartir"
à zéro avec toutes nos boîtes vides, il suffit d'appuyer sur la touche R
de notre clavier.

_Mode "Debug"_

Si nous voulons observer le niveau d'énergie des souris ainsi que l'énergie
des fromages, nous avons un mode dans le laboratoire qui permet cela.
Il suffit de taper:

* Touche "D" du clavier : quand l'on appuie sur cette touche, notre lab
passe en mode "debug", et nous pouvons observer les comportements des 
souris en temps réél.

**Fonctionnalités de l'organe:**

Nous voila dans la vue "organe" de notre programme. Nous pouvons y voir
notre foie ainsi que le réseau sanguin de notre souris.
Voici quelques fonctionnalités que l'on peut avoir:

* Touche "X" du clavier : Ajout d'une cellule cancéreuse. Si l'on place 
notre curseur près du réseau sanguin irrigué et qu'on ajoute une cellule
cancéreuse, après un certain temps on devrait voir cette dernière se diviser
et s'étendre petit à petit.
Si l'on place notre curseur en dehors de la région irriguée par le réseau
sangin, l'on devrait voir notre cellule cancéreuse disparaître après un 
certain moment.

* Touche "N" du clavier : Changement de substance diffusée. Quand l'on
appuie sur cette touche, en haut à droite sous "Current Substance" on 
devrait voir changer le nom de la substance diffusée; passer de "Glucose" 
à  "Bromo", à "VGEF", puis revenir à "Glucose".
Cela nous permet de choisir quelle substance l'on voudrait diffuser.

* Touche "2" ou "PageUp" : Augmenter la quantité de substance diffusée. 
Note : Si l'on augmente la quantité de BROMOPYRUVATE, cela va faire en 
sorte que le cancer arrête de se multiplier et s'étendre, puis va disparaître 
si la quantité de l'inhibiteur est suffisante. 
Une fois les cellules cancéreuses disparues, le foie devrait pouvoir se régénérer.

* Touche "3" ou "PageDown" : Diminuer la quantité de substance diffusée.

_Mode "Concentration"_

Si nous voulons observer les substances se diffuser en temps réel lorsque
nous augmentons la quantité des substances, il faut appuyer sur:

* Touche "S" : Passer en mode "concentration" pour ainsi observer la
diffusion de nos substances. (cela peut prendre un petit peu de temps avant
de pouvoir voir la diffusion s'opérer).
On peut toujours changer de substance en appuyant sur la touche "N" et 
augmenter/diminuer la quantité en appuyant sur "2" ou "3". 
Il suffit de re-taper la touche "S" pour revenir sur la vue organe.

_Revenir dans le laboratoire:_

* Touche "L" : Si l'on veut revenir dans la vue "Lab", il suffit de taper
la touche L pour changer de vue.

**Quelques tests spécifiques utiles:**

* scons SubstControlTest-run --cfg=appDiff.json : contrôle de la diffusion
des substances. Pour bien visualiser les substances diffusées.

###Modifications apportées pour les tests:

* BloodSystemTest:
Nous avons modifiées les touches: touches "1" à la place de "+" et "2" à la place
de "-".

