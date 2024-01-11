[![C/C++ CI](https://github.com/Lucass307/OpenSourceIT/actions/workflows/c.yml/badge.svg)](https://github.com/Lucass307/OpenSourceIT/actions/workflows/c.yml)

![GitHub issues](https://img.shields.io/github/issues-raw/Lucass307/OpenSourceIT)

## Systèmes d'Exploitation

![Windows](https://img.shields.io/badge/Windows-Supported-brightgreen)
![MacOS](https://img.shields.io/badge/MacOS-Supported-brightgreen)
![Linux](https://img.shields.io/badge/Linux-Supported-brightgreen)

# OpenSourceIT

vigenere_file - Un programme en langage C qui permet de chiffrer le contenu d'un fichier avec la méthode de Vigenère.

## Description

Ce programme a pour fonction la lecture d'un texte à partir d'un fichier texte, puis applique méthode de chiffrement Vigenère avec une clé spécifiée, que ce soit pour encoder un message confidentiel ou décoder une communication cryptée. Une fois le processus de chiffrement ou de déchiffrement accompli, le résultat est affiché sur la sortie standard, offrant ainsi une solution polyvalente et pratique pour sécuriser ou interpréter des messages texte de manière confidentielle.

## Installation 

### Prérequis
* GCC (GNU Compiler Collecton)

Pour bénéficier du programme sur votre machine, suivez les étapes d'installation suivantes :

### installation sur Windows
1. Installer MSYS2
Si vous n'avez pas déjà MSYS2 installé, téléchargez-le à partir du site officiel : [MSYS2](https://www.msys2.org/)

2. Installer GCC (GNU Compiler Collection)
Une fois MSYS2 installé, ouvrez le terminal MSYS2 et exécutez la commande suivante pour installer GCC :

```bash
pacman -S mingw-w64-x86_64-gcc
```

### Installation sur MacOS
Sur MacOs, vous pouvez utiliser le gestionnaire de paquets Homebrew pour installer GCC.
Si vous n'avez pas encore Homebrew, installez-le en suivant les instructions sur le [site officiel](https://brew.sh/). Ensuite, exécutez la commande suivante :

```bash
brew install gcc
```

### Installation sur Linux (Ubuntu)
Sur Linux, utilisez le gestionnaire de paquets pour installer GCC. 

```bash
sudo apt-get update
sudo apt-get install build-essential
```

## Utilisation

Après avoir cloné le dépôt Git et installé les dépendances nécessaires, voici les étapes à suivre pour lancer le programme : 
1. Lancez le terminal :
* MacOs : ouvrez Terminal
* Linux (Ubuntu) : ouvrez le terminal approprié pour votre distribution (par exemple Terminal sur Ubuntu)
* Windows : ouvrez le terminal MSYS2
3. Utilisez la commande 'cd' pour vous déplacer vers le répertoire dans lequel est cloné le dépôt Git.
4. Compilez le code avec gcc
```bash
gcc -o exe vigenere_file.c
```
4. Exécutez le programme en précisant la clé suivie de l'option de déchiffrement si l'on veut (si rien est précisé on chiffrera) :
```bash
./exe [fichier][cle] (decode)
```
Une fois le programme lancé, si votre programme demande à l'utilisateur de spécifier le nom du fichier à traiter, entrez le nom du fichier ou le chemin complet comme demandé.

## Contribution

N'hésitez pas à contribuer au projet !
Votre contribution est la bienvenue, si vous souhaitez nous en faire part, suivez ces étapes :

1. Fork du projet.
2. Créez une branche pour votre fonctionnalité (git checkout -b feature/nouvelle-fonctionnalite).
3. Commitez vos modifications (git commit -m 'Ajout de la nouvelle fonctionnalité').
4. Poussez vers la branche (git push origin feature/nouvelle-fonctionnalite).
5. Créez une nouvelle Pull Request.

