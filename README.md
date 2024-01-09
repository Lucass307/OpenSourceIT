# OpenSourceIT

- Un jeu en C inspiré du célèbre Pokemon 

## Description

Jeu de combat stratégique en langage C. Collectionnez, évoluez et combattez avec des créatures personnalisées. Affrontez d'autres joueurs virtuels et montez en niveau en remportant un maximum de victoires !

## Installation 

### Prérequis
* MSYS2
* GCC (GNU Compiler Collecton)
* SDL Library

Pour jouer à ce jeu, suivez les étapes d'installation suivantes : 

### 1. Installer MSYS2

Si vous n'avez pas déjà MSYS2 installé, téléchargez-le à partir du site officiel : [MSYS2](https://www.msys2.org/)

### 2. Installer GCC (GNU Compiler Collection)

Une fois MSYS2 installé, ouvrez le terminal MSYS2 et exécutez la commande suivante pour installer GCC :

```bash
pacman -S mingw-w64-x86_64-gcc
```

### 2. Installer SDL Library
Toujours dans le terminal MSYS2, exécutez la commande suivante pour installer la bibliothèque SDL :

```bash
pacman -S mingw-w64-x86_64-SDL2
```

## Utilisation

Après avoir cloné le dépôt Git et installé les dépendances nécessaires, voici les étapes à suivre pour jouer au jeu : 
1. Lancez le terminal MSYS2
2. Utilisez la commande 'cd' pour vous déplacer vers le répertoire dans lequel est cloné le dépôt Git.
3. Compilez le code avec la commande 'make'.
4. Exécutez le jeu avec la commande :
```bash
./nom_du_jeu
```
Une fois le jeu lancé, suivez les instructions à l'écran pour jouer. Cela peut inclure l'utilisation certaines touches du clavier ou de la souris.

## Contribution

N'hésitez pas à contribuer au projet !
Votre contribution est la bienvenue, si vous souhaitez nous en faire part, suivez ces étapes :

1. Fork du projet.
2. Créez une branche pour votre fonctionnalité (git checkout -b feature/nouvelle-fonctionnalite).
3. Commitez vos modifications (git commit -m 'Ajout de la nouvelle fonctionnalité').
4. Poussez vers la branche (git push origin feature/nouvelle-fonctionnalite).
5. Créez une nouvelle Pull Request.

