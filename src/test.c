#include <./unity/unity.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vigenere_file.h"

// Inclure le code que vous souhaitez tester
void setUp(void) {
    // Initialiser avant chaque test si nécessaire
}

void tearDown(void) {
    // Nettoyer après chaque test si nécessaire
}

void test_vigenere_encrypt() {
    // Test case 1
    FILE *input1 = fopen("test_input1.txt", "w");
    fputs("HELLO", input1);
    fclose(input1);

    // Ouvrir le fichier en mode lecture
    input1 = fopen("test_input1.txt", "r");

    FILE *result1 = fopen("test_output1.txt", "w");

    vigenere(input1, "KEY", 1, result1);
    fclose(input1);  // Fermez le fichier avant de le rouvrir
    fclose(result1);
    // Lire le résultat à partir du fichier de sortie
    result1 = fopen("test_output1.txt", "r");
    char buffer1[1024];
    fgets(buffer1, 1024, result1);
    fclose(result1);

    // Ajoutez ces instructions d'affichage
    printf("Expected: RIJVS\n");
    printf("Actual  : %s\n", buffer1);

    result1 = fopen("test_output1.txt", "r");
    rewind(result1);
    printf("Output for encrypt: %s\n", buffer1);
    TEST_ASSERT_EQUAL_STRING("RIJVS", buffer1);
    fclose(result1);
}
/*void printFileContents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
    putchar('\n');
}
void test_vigenere_decrypt() {
    // Ouvrir le fichier chiffré en mode lecture
    FILE *output1 = fopen("test_output1.txt", "r");

    FILE *result2 = fopen("test_output2.txt", "w");

    // Fermez le fichier output1 avant de le rouvrir
    fclose(output1);

    // Déchiffrer le texte et écrire le résultat dans un autre fichier
    output1 = fopen("test_output1.txt", "r");
    vigenere(output1, "KEY", 0, result2);  // Mettez le troisième paramètre à 0 pour le déchiffrement

    // Fermez les fichiers
    fclose(output1);
    fclose(result2);

    // Ajoutez ces instructions d'affichage
    printf("Après déchiffrement, contenu de output1 : ");
    printFileContents("test_output1.txt");

    // Lire le résultat à partir du fichier déchiffré
    result2 = fopen("test_output2.txt", "r");
    char buffer1[1024];
    fgets(buffer1, 1024, result2);
    fclose(result2);

    // Ajoutez ces instructions d'affichage
    printf("Attendu : HELLO\n");
    printf("Réel    : %s\n", buffer1);

    // Vérifier que le résultat déchiffré est correct
    TEST_ASSERT_EQUAL_STRING("HELLO", buffer1);
}

*/

int main(void) {
    UNITY_BEGIN();

    // Exécuter vos tests
    RUN_TEST(test_vigenere_encrypt);
    /*RUN_TEST(test_vigenere_decrypt);*/

    return UNITY_END();
}
