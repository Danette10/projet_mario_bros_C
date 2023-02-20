# Comment lancer le projet ?

1. Pour lancer le projet il suffit de télécharger tout le projet et ouvrir un terminal
> `MSYS2 MINGW64` sur Windows
>
> Terminal classique sur linux

2. Il faut également avoir installé en amont ``gcc`` que ce sois sur windows, linux ou autre

3. Une fois le terminal ouvert, déplacez-vous à la racine du projet à l'aide de la commande : `cd`

4. Pour finir vous pouvez tout simplement exécuter la commande suivante : 
>`make all`


# Contexte et organisation du groupe

Nous n'avons pas mis en place de planning à proprement parlé mais nous nous étions organisés de manière à nous réunir sur place au moins 1 fois par semaine.

Les taches ont été effectuées de la manière suivante :

### Dan

- Menu
- Déplacement du joueur en déplaçant le background
- Mouvement infini de l'ennemi
- Tout les évènements clavier pour le déplacement du joueur et des objets
- Système de gravité
- Compte le nombre de gameover

### Mamadou

- Dégats des ennemis et du joueur
- Collision entre les différents objets du jeu

### Kano

- Création et effets des différents objets (champignons...)
- Level design

### Dan, Mamadou, Kano

- Musique
- Mort du joueur et des ennemis
- Fenetre du GameOver

# Organisation du code

Le code a été organisé de manière à pouvoir modifier ou réparer des bugs facilement.
Toutes les fonctions du code ont des prototypes.
Par exemple la fonction `handleMenuNavigation` n'est pas déclarée dans `menu.c` mais elle est déclarée dans le fichier `menu.h`, ainsi les fonctions de notre projet sont beaucoup mieux organisées et on a donc une meilleure visibilité sur les fonctions.

Nos fonctions, objets sont structurés comme par exemple :

```c
// Structure for the player  
typedef struct {  
    char *name;  
    char *imagePath;  
    SDL_Texture *texture;  
    SDL_Rect rect;  
    int pv;  
} Player;
```

Nous pensons que ces choix sont pertinents car il permet d'ajouter facilement et rapidement de nouveaux attributs pour un objet, notre code est ainsi plus facilement maintenable, plus lisible et surtout structuré.

# Fonctionnalités du projet

- Déplacement du joueur (droite, gauche, saut, saut + droite)
- Tuer un ennemi
- Collision entre les différents objets
- Obtension d'un bonus en rentrant en collision avec des objets le permettant tel que les champignons.
- Savoir combien de fois on à perdu

# Problèmes rencontré

Les problèmes que nous avons rencontrés c'était pour l'ajout de musique dans le jeu avec SDL_Mixer, au final nous avons utilisé SDL_Audio mais nous n'avons malheureusement pas pu ajouter des effets sonores lors du saut..., car il y avait un décalage entre le moment du saut et du son et nous n'avons pas réussi à régler ce problème par manque de temps.

# Ressenti individuel

## Dan

Il n'y a pas réellement de concordance entre ce projet et ma formation à l'ESGI, mis à part le fait que j'aime beaucoup le code et que des lignes puissent créer un véritable projet, je trouve cela fascinant et j'aime beaucoup le développement quel qu'il soit. 

J'ai beaucoup aimé réaliser ce projet car j'ai pu mettre en oeuvre des notions vues en cours tel que les structures, les prototypes...

Etant également un grand fan de Mario, pouvoir réaliser un Mario Bros comme projet de cours était réellement amusant et captivant, j'avais toujours envie de continuer son développement. 
Grâce à celui-ci j'ai également pu approfondir mes connaissances en langage C en utilisant aussi une bibliothèque externe comme la SDL2 pour notre projet.

Votre cours de langage C m'a beaucoup appris et sans vos supports de cours ou vos explications pendant les heures de cours, nous aurions surement mis beaucoup plus de temps à la réalisation de ce projet

Je suis néanmoins déçu de ne pas avoir réussi à aller plus loin dans la réalisation du projet et ne pas avoir réussi à mettre en place les fonctionnalités que nous avions prévu d'implémenter par manque de temps.

Je continuerais sans doute le développement de ce projet après la soutenance de celui-ci.


## Mamadou

Ce cours nous a vraiment aidés sur tous les plans grâce à son contenu remarquable. Il nous a permis de travailler sur chaque chapitre afin de savoir ce que chaque élément est, comment il est utilisé et quand il doit être utilisé.
Nous avons également appris à utiliser des bibliothèques telles que ncurses et même SDL. 
J'ai beaucoup aimé réaliser ce projet, car je n'imaginais pas du tout qu'une telle chose était possible. De plus, avec notre excellent groupe, la moitié du travail a pu être accomplie. Grâce à notre connaissance de l'utilisation de SDL, nous avons progressé bien plus rapidement que prévu.


## Kano

L'ESGI est une école réputée par son enseignement de qualité. Par conséquent tous les cours qui y sont dispensés sont une partie intégrante de notre réussite professionnelle. Ce cours m'a initié à la programmation informatique. j'ai appris les bases du langage C, mais aussi des notions plus avancées qui m'ont permis d'être autonomes pour n'importe quel projet. 
Ce cours m'a également aidé à faire le choix de ma spécialisation. 
En effet, le langage C n'est pas ma matière préférée mais elle participe au développement de mes capacités à devenir polyvalente. Par le biais de ce projet, j'ai pu découvrir de nouvelle connaissance et savoir-faire comme programmer un jeu et créer une interface dynamique avec des notions de cours et de recherche approfondie. j'ai bien aimé ce projet car cela m'a permis de voir tout le travaille minutieux que font les développeurs de jeux et cela est à la porter de tous.