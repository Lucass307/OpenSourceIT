# Utilisation


## Après avoir installé les dépendances nécessaires, clonez le dépot git du projet !

Cloner le Projet : Clonez le projet depuis le dépôt GitHub :

    git clone https://github.com/nom-utilisateur/OpenSourceIT.git

Remplacez `nom-utilisateur` par vos informations.

## Ensuite, suivez ces instructions pour éxecuter le programme : 

Entrer dans le Répertoire du Projet :

```bash
cd OpenSourceIT/
```

Compilez le code avec gcc :
```bash
gcc -o myprogram ./src/vigenere_file.c ./src/main.c
```

Exécutez le programme en précisant le fichier cible suivie de la clé de chiffrement, ainsi que de l'option de déchiffrement si l'on veut (si rien est précisé on chiffrera) :
```bash
./myprogram [fichier] [cle] (decode)
```
Une fois le programme lancé, si votre programme demande à l'utilisateur de spécifier le nom du fichier à traiter ainsi que sa clé, pensez à bien entrer le chemin du fichier ainsi que la clé correspondante.

### Important ! Si vous décidez d'encoder un fichier, le fichier codé se renommera [fichier]_encode.txt.
### Si c'est décoder, le fichier se nommera [fichier]_decode.txt
