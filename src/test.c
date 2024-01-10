#include <unity.h>
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

    char *argv1[] = {"program_name", "test_input1.txt", "KEY"};
    vigenere_main(3, argv1);

    FILE *result1 = fopen("test_output1.txt", "r");
    char buffer1[1024];
    fgets(buffer1, sizeof(buffer1), result1);
    fclose(result1);

    TEST_ASSERT_EQUAL_STRING("RIJVS", buffer1);
}

void test_vigenere_decrypt() {
    // Test case 1
    FILE *input1 = fopen("test_input1.txt", "w");
    fputs("RIJVS", input1);
    fclose(input1);

    char *argv1[] = {"program_name", "test_input1.txt", "KEY", "decode"};
    vigenere_main(4, argv1);

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