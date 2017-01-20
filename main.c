#include <stdio.h>
#include <stdlib.h>

// Reading dictionary john file (john.txt)
FILE *f = fopen("john.txt", "rb");
fseek(f, 0, SEEK_END);
long fsize = ftell(f);
fseek(f, 0, SEEK_SET);
char *string = malloc(fsize + 1);
fread(string, fsize, 1, f);
fclose(f);
string[fsize] = 0;

// Encrypt file
