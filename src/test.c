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

void test_vigenere_encrypt() {
    // Test case 1
    FILE *input1 = fopen("test_input1.txt", "w");
    fputs("HELLO", input1);
    fclose(input1);

    char *argv1[] = {"program_name", "test_input1.txt", "KEY"};
    main(3, argv1);

    FILE *result1 = fopen("test_output1.txt", "r");
    char buffer1[1024];
    fgets(buffer1, sizeof(buffer1), result1);
    fclose(result1);

    TEST_ASSERT_EQUAL_STRING("RIJVS", buffer1);

    // Test case 2
    FILE *input2 = fopen("test_input2.txt", "w");
    fputs("WORLD", input2);
    fclose(input2);

    char *argv2[] = {"program_name", "test_input2.txt", "KEY"};
    main(3, argv2);

    FILE *result2 = fopen("test_output2.txt", "r");
    char buffer2[1024];
    fgets(buffer2, sizeof(buffer2), result2);
    fclose(result2);

    TEST_ASSERT_EQUAL_STRING("ZVJNQ", buffer2);
}

void test_vigenere_decrypt() {
    // Test case 1
    FILE *input1 = fopen("test_input1.txt", "w");
    fputs("RIJVS", input1);
    fclose(input1);

    char *argv1[] = {"program_name", "test_input1.txt", "KEY", "decode"};
    main(4, argv1);

    FILE *result1 = fopen("test_output1.txt", "r");
    char buffer1[1024];
    fgets(buffer1, sizeof(buffer1), result1);
    fclose(result1);

    TEST_ASSERT_EQUAL_STRING("HELLO", buffer1);

    // Test case 2
    FILE *input2 = fopen("test_input2.txt", "w");
    fputs("ZVJNQ", input2);
    fclose(input2);

    char *argv2[] = {"program_name", "test_input2.txt", "KEY", "decode"};
    main(4, argv2);

    FILE *result2 = fopen("test_output2.txt", "r");
    char buffer2[1024];
    fgets(buffer2, sizeof(buffer2), result2);
    fclose(result2);

    TEST_ASSERT_EQUAL_STRING("WORLD", buffer2);
}

int test_program_main(void) {
    UNITY_BEGIN();

    // Exécutez vos tests
    RUN_TEST(test_vigenere_encrypt);
    RUN_TEST(test_vigenere_decrypt);

    return UNITY_END();
}
