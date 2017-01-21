#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_MAX_LENGTH 256

void output(int rows, char p[][BUFFER_MAX_LENGTH+1]){
  int i,j;
  for(i=0;i<rows;i++){
    printf("%d : ",i);
    // printf("%s",p[i]);
    for(j=0;j<BUFFER_MAX_LENGTH && p[i][j]!='\0';j++){
      printf("%c",p[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char const *argv[]) {

  // Reading dictionary john file (john.txt)
  FILE *file = NULL;
  char line[BUFFER_MAX_LENGTH+1];
  int tempChar;
  int lines = 0;
  int tempCharIdx = 0;


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

  printf("Total lines %i\n", lines);

  char array[lines][BUFFER_MAX_LENGTH+1];
  int i=0;
  /* get a character from the file pointer */

  fseek(file, 0, SEEK_SET);//Reseating file to read again

  //Reading file again
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
          // printf("%i: %s\n",i,array[i][0]);
          // fprintf(stdout, "%s\n", line);
          break;
      }
      else if (tempChar == '\n') {
          line[tempCharIdx] = '\0';
          array[i][tempCharIdx] = '\0';
          i++;
          tempCharIdx = 0;
          // printf("%i: %s\n",i,array[i][0]);
          // fprintf(stdout, "%s\n", line);
          continue;
      }
      else{
        array[i][tempCharIdx] = (char)tempChar;
        // printf("[%i,%i]:%c",i,tempCharIdx,array[i][tempCharIdx]);
        line[tempCharIdx++] = (char)tempChar;
      }
  }

  printf("Original \n");
  // printf("Test %c%c%c%c%c\n",array[0][0],array[0][1],array[0][2],array[0][3],array[0][4]);
  output(lines,array);
  //printf("String size %ld: %s",fsize,string);

  //Initial Sort in descending order
  int c,d;
  char swap[BUFFER_MAX_LENGTH + 1];
  for (c = 0 ; c < ( lines - 1 ); c++)
  {
    for (d = 0 ; d < lines - c - 1; d++)
    {
      // if (array[d][0] < array[d+1][0])
      if (strcmp(array[d],array[d+1])< 0)
      {
        strncpy(swap, array[d], BUFFER_MAX_LENGTH + 1);
        strncpy(array[d], array[d+1], BUFFER_MAX_LENGTH + 1);
        strncpy(array[d+1], swap, BUFFER_MAX_LENGTH + 1);
      }
    }
  }

  printf("Sorted \n");
  output(lines,array);

  // Remove duplicated
  char tempValue[BUFFER_MAX_LENGTH + 1];
  int countRemoved = 0;
  for(c=0;c<lines - 1;c+=2){
    if (strcmp(array[c],array[c+1]) == 0){
      //Delete
      strcpy(array[c+1], "");
      countRemoved++;
    }
  }
  char finalarray[lines-countRemoved][BUFFER_MAX_LENGTH+1];
  d=0;
  for(c=0;c<lines;c++){
    if (strcmp(array[c],"") != 0){
      // Add to final string
      strncpy(finalarray[d++], array[c], BUFFER_MAX_LENGTH + 1);
    }
  }
  printf("Unique \n");
  output(lines-countRemoved,finalarray);
  // Implement
  // -c Precede each output line with the count of the number of times the line occurred in the input, followed by a single space.
  // -i Case insensitive comparison of lines.
  // -w compare no more than N characters in lines
  return 0;
}
