# Utilisation


## Après avoir installé les dépendances nécessaires, clonez le dépot git du projet !

Ensuite, suivez ces instructions pour éxecuter le programme : 

Compilez le code avec gcc
gcc -o myprogram ./src/vigenere_file.c ./src/main.c

Exécutez le programme en précisant le fichier cible suivie de la clé de chiffrement, ainsi que de l'option de déchiffrement si l'on veut (si rien est précisé on chiffrera) :
./myprogram [fichier][cle] (decode)

Une fois le programme lancé, si votre programme demande à l'utilisateur de spécifier le nom du fichier à traiter ainsi que sa clé, pensez à bien entrer le chemin du fichier ainsi que la clé correspondante.
