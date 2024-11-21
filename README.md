<a name="readme-top"></a>
<div align="center">
  <a href="https://github.com/Arnaud-Bnd/Marc_Project_BERNARD_LASSOUT_GARCIA_ARNOULT"></a>

<h2 align="center">Rover Run!</h2>
<h5 align="center">Réalisé par Arnaud Bernard, Marc-Antoine Lassout, Laetitia Arnoult et Ivana Garcia</h5>

<p align="center">
    Rover Run! est un projet où nous incarnons une équipe d'expert en programmation devant venir en aide à l'ESTF. Notre mission est de concevoir un logiciel de déplacement pour ramener MARC, leur rover, à une station de base sachant que MARC a été endommagé par une tempête solaire.
</p>
</div>

## Déroulement du Projet
Pour réaliser ce logiciel de déplacement qui doit secourir MARC, nous devons réaliser 3 étapes.
- L'étape 1 consiste au développement des structure de données pour l'arbre de sélection des déplacements et de créer un arbre avec 3 choix parmi 4 ou 5 valeurs possibles. Cette étape a été primordiale pour correctement mettre au point les algorithmes de construction de l'arbre ainsi que ceux de la recherche de la feuille de valeur minimale  et du chemin depuis la racine vers cette feuille.

- L'étape 2 est le passage à l'échelle de nos précédents algorithmes afin d'arriver jusqu'au choix de 5 mouvements parmi 9 possibilités. Afin de vérifier l'optimisation du programme, nous avons réaliser l'étude des temps d'exécution de notre programme pour:
    - La phase de construction de l'arbre
    - La phase de recherche d'une feuille de valeur minimale parmi toutes les feuilles de l'arbre
    - Le calcul du chemin de la racine vers cette feuille
    - Un exemple complet de guidage de MARC depuis sa position d'origine vers la station de base
  Nous avons aussi élaborer un algorithme nosu permettant d'inventer nos propres cartes géographiques de MARC afin de mettre notre programme à l'épreuve.

- L'étape 3 nous a permis d'améliorer l'interface graphique de notre logiciel afin de le rendre plus compréhensible. 

## Structure
- Le fichier loc.h contient les prototypes et les structures permettant de déplacer notre rover MARC
- Le fichier loc.c contient toutes les fonctions permettant de guider le rover MARC
- Le fichier map.h contient les structures et les prototypes des fonctions permettant de créer et de gérer des cartes géographiques de notre rover MARC
- Le fichier map.c contient toutes les fonctions énoncées dans le fichier précédent
- Le fichier moves.h contient les prototypes de fonctions permettant de fixer ou de modifier la localisation du rover MARC
- Le fichier moves.c contient toutes les fonctions énoncées dans le fichier précédent
- Le fichier queue.h contient tous les prototypes des fonctions permettant de manipuler des files
- Le fichier queue.c contient toutes les fonctions énoncées dans le fichier précédent
- Le fichier stack.h contient tous les prototypes des fonctions permettant de manipuler des piles
- Le fichier stack.c contient toutes les fonctions énoncées dans le fichier précédent
- Le fichier tree_functions.h contient les prototypes de notre logiciel ainsi que les structures associées à notre arbre N-aire
- Le fichier tree_functions.c contient toutes les fonctions permettant de manipuler et de lire cet arbre N-aire afin d'élaborer le chemin que devra emprunter le rover MARC
- Le fichier main.c est le fichier où le chemin est trouvé par notre logiciel et est transmis au rover MARC débutant ainsi son guidage
