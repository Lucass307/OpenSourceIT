# OpenSourceIT

vignr - Un programme en langage C qui permet de chiffrer le contenu d'un fichier avec la méthode de Vigenère.

## Description

Ce programme a pour fonction la lecture d'un texte à partir d'un fichier texte, puis applique méthode de chiffrement Vigenère avec une clé spécifiée, que ce soit pour encoder un message confidentiel ou décoder une communication cryptée. Une fois le processus de chiffrement ou de déchiffrement accompli, le résultat est affiché sur la sortie standard, offrant ainsi une solution polyvalente et pratique pour sécuriser ou interpréter des messages texte de manière confidentielle.

## Installation 

### Prérequis
* MSYS2
* GCC (GNU Compiler Collecton)

Pour bénéficier du programme sur votre machine, suivez les étapes d'installation suivantes : 

### 1. Installer MSYS2

Si vous n'avez pas déjà MSYS2 installé, téléchargez-le à partir du site officiel : [MSYS2](https://www.msys2.org/)

### 2. Installer GCC (GNU Compiler Collection)

Une fois MSYS2 installé, ouvrez le terminal MSYS2 et exécutez la commande suivante pour installer GCC :

```bash
pacman -S mingw-w64-x86_64-gcc
```

## Utilisation

Après avoir cloné le dépôt Git et installé les dépendances nécessaires, voici les étapes à suivre pour lancer le programme : 
1. Lancez le terminal MSYS2
2. Utilisez la commande 'cd' pour vous déplacer vers le répertoire dans lequel est cloné le dépôt Git.
3. Compilez le code avec gcc
```bash
gcc vigenere_file.c -o nom_du_programme
```
4. Exécutez le programme avec la commande :
```bash
./vigenere_file.c
```
Une fois le programme lancé, suivez les instructions à l'écran : Si votre programme demande à l'utilisateur de spécifier le nom du fichier à traiter, entrez le nom du fichier ou le chemin complet comme demandé.

## Contribution

N'hésitez pas à contribuer au projet !
Votre contribution est la bienvenue, si vous souhaitez nous en faire part, suivez ces étapes :

1. Fork du projet.
2. Créez une branche pour votre fonctionnalité (git checkout -b feature/nouvelle-fonctionnalite).
3. Commitez vos modifications (git commit -m 'Ajout de la nouvelle fonctionnalité').
4. Poussez vers la branche (git push origin feature/nouvelle-fonctionnalite).
5. Créez une nouvelle Pull Request.

