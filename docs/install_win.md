# Installation de GCC sur MSYS2

## 1. Installer MSYS2

Si vous n'avez pas encore installé MSYS2, téléchargez le [programme d'installation de MSYS2](https://www.msys2.org/) depuis le site officiel.

## 2. Lancer MSYS2 et Mettre à Jour le Système

Une fois MSYS2 installé, lancez le programme et ouvrez la console (le terminal MSYS2). Exécutez les commandes suivantes pour mettre à jour le système :

```bash
pacman -Syu
```

Pour installer GCC, exécutez la commande suivante dans le terminal MSYS2 :

```bash
pacman -S mingw-w64-x86_64-gcc
```

Une fois l'installation terminée, vous pouvez vérifier que GCC est correctement installé en exécutant la commande suivante :

```bash
gcc --version
```
