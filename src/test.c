#include <unity.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclure le code que vous souhaitez tester
#include "vigenere_file.h"

void setUp(void) {
    // Initialiser avant chaque test si nécessaire
}

void tearDown(void) {
    // Nettoyer après chaque test si nécessaire
}

void run_program(char *input_file, char *key, char *output_file, int is_decode) {
    char *argv[5];
    argv[0] = "program_name";
    argv[1] = input_file;
    argv[2] = key;
    argv[3] = is_decode ? "decode" : "";
    argv[4] = NULL;

    // Appeler votre fonction vigenere_main avec les arguments
    vigenere_main(is_decode ? 4 : 3, argv);
}

void test_vigenere_encrypt() {
    // Exécuter votre programme pour chiffrer
    run_program("test_input1.txt", "KEY", "test_output1.txt", 0);

    // Lire le fichier résultant et vérifier le résultat
    FILE *result1 = fopen("test_output1.txt", "r");
    char buffer1[1024];
    fgets(buffer1, sizeof(buffer1), result1);
    fclose(result1);

    TEST_ASSERT_EQUAL_STRING("RIJVS", buffer1);
}

void test_vigenere_decrypt() {
    // Exécuter votre programme pour déchiffrer
    run_program("test_input1.txt", "KEY", "test_output1.txt", 1);

    // Lire le fichier résultant et vérifier le résultat
    FILE *result1 = fopen("test_output1.txt", "r");
    char buffer1[1024];
    fgets(buffer1, sizeof(buffer1), result1);
    fclose(result1);

    TEST_ASSERT_EQUAL_STRING("HELLO", buffer1);
}

int test_program_main(void) {
    UNITY_BEGIN();

    // Exécuter vos tests
    RUN_TEST(test_vigenere_encrypt);
    RUN_TEST(test_vigenere_decrypt);

    return UNITY_END();
}
