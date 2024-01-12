# Installation de GCC sur Debian/Ubuntu et Arch Linux

## Debian/Ubuntu

Sur Debian et Ubuntu, vous pouvez utiliser la commande `apt-get` pour installer GCC. Assurez-vous d'avoir les dernières informations sur les paquets avant d'installer :

```bash
sudo apt-get update
sudo apt-get install build-essential
```

## Arch Linux

Sur Arch Linux, utilisez pacman :

```bash
sudo pacman -S gcc
```

Après l'installation, vous pouvez vérifier que GCC est correctement installé en exécutant la commande suivante dans le terminal :


```bash
gcc --version
```
