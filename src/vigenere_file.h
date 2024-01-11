// vigenere_file.h
#ifndef VIGENERE_FILE_H
#define VIGENERE_FILE_H

#include <stdio.h>

void vigenere(FILE *input, char *cle, int sign, FILE *output);
void vigenere_main(int argc, char *argv[]);
int vigenere_program_main(int argc, char *argv[]);

#endif
