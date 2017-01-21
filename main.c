#include <stdio.h>
#include <stdlib.h>
#define BUFFER_MAX_LENGTH 256

int main(int argc, char const *argv[]) {

  // Reading dictionary john file (john.txt)
  FILE *file = NULL;
  char line[BUFFER_MAX_LENGTH];
  int tempChar;
  int lines = 0;
  unsigned int tempCharIdx = 0U;


  if (argc == 2)
       file = fopen(argv[1], "r");
  else {
       fprintf(stderr, "error: filename argument not found\n"
                       "usage: %s john.txt\n", argv[0]);
       return EXIT_FAILURE;
  }

  if (!file) {
       fprintf(stderr, "error: could not open file: %s\n", argv[1]);
       return EXIT_FAILURE;
  }

  // Counting Lines to create array
  while(fgets(line,BUFFER_MAX_LENGTH,file) != NULL)
  {
    lines++;
  }

  printf("Total lines %i", lines);

  char array[lines][BUFFER_MAX_LENGTH];
  int i=0;
  /* get a character from the file pointer */
  while((tempChar = fgetc(file)))
  {
      /* avoid buffer overflow error */
      if (tempCharIdx == BUFFER_MAX_LENGTH) {
          fprintf(stderr, "error: line is longer than 256 characters.\n");
          return EXIT_FAILURE;
      }

      /* test character value */
      if (tempChar == EOF) {
          line[tempCharIdx] = '\0';
          array[i][tempCharIdx] = '\0';
          i++;
          fprintf(stdout, "%s\n", line);
          break;
      }
      else if (tempChar == '\n') {
          line[tempCharIdx] = '\0';
          tempCharIdx = 0U;
          array[i][tempCharIdx] = '\0';
          i++;
          fprintf(stdout, "%s\n", line);
          continue;
      }
      else{
        array[i][tempCharIdx] = (char)tempChar;
        line[tempCharIdx++] = (char)tempChar;
      }
  }

  //printf("String size %ld: %s",fsize,string);

  // Sort in descending order
  // int c,n,d,swap
  // for (c = 0 ; c < ( n - 1 ); c++)
  // {
  //   for (d = 0 ; d < n - c - 1; d++)
  //   {
  //     if (array[d] > array[d+1]) /* For decreasing order use < */
  //     {
  //       swap       = array[d];
  //       array[d]   = array[d+1];
  //       array[d+1] = swap;
  //     }
  //   }
  // }

  // Remove duplicated
  // Implement
  // -c Precede each output line with the count of the number of times the line occurred in the input, followed by a single space.
  // -i Case insensitive comparison of lines.
  // -w compare no more than N characters in lines
  return 0;
}
