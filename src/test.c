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

/*void test_vigenere_decrypt() {
    // Test case 1
    FILE *input1 = fopen("test_input1.txt", "w");
    fputs("RIJVS", input1);
    fclose(input1);

    char *argv1[] = {"myprogram", "test_input1.txt", "KEY", "decode"};
    printf("Running decrypt test with arguments: ");
    for (int i = 0; i < 4; ++i) {
        printf("%s ", argv1[i]);
    }
    printf("\n");

    vigenere_main(4, argv1);

    FILE *result1 = fopen("test_output1.txt", "r");
    char buffer1[1024];
    fgets(buffer1, sizeof(buffer1), result1);
    fclose(result1);

    printf("Output for decrypt: %s\n", buffer1);
    TEST_ASSERT_EQUAL_STRING("HELLO", buffer1);
}*/

int main(void) {
    UNITY_BEGIN();

    // Exécuter vos tests
    RUN_TEST(test_vigenere_encrypt);
    // RUN_TEST(test_vigenere_decrypt);

    return UNITY_END();
}