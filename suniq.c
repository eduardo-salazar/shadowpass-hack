#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFFER_MAX_LENGTH 256
void normal_output(int rows, char p[][BUFFER_MAX_LENGTH+1]){
  int i,j;
  // printf("\n");
  for(i=0;i<rows;i++){
    // printf("%d : ",i);
    for(j=0;j<BUFFER_MAX_LENGTH && p[i][j]!='\0';j++){
      printf("%c",p[i][j]);
    }
    printf("\n");
  }
}

void count_output(int count, char p[BUFFER_MAX_LENGTH+1]){
  int j;
  // printf("\n");
  printf("%d ",count);
  for(j=0;j<BUFFER_MAX_LENGTH;j++){
    printf("%c",p[j]);
  }
  printf("\n");
}

int hasOpt(int argc,char **argv, char op){
  int i;
  for(i=0;i<argc;i++){
    if(strstr(argv[i], "-")){
      if(strchr(argv[i], op)){
        return 1;
      }
    }
  }
  return 0;
}

int getOptValue(int argc,char **argv, char op){
  int i,value;
  for(i=0;i<argc;i++){
    if(strstr(argv[i], "-")){
      if(strchr(argv[i], op)){
        value = atoi(argv[i+1]);
        // printf("Value %i",value);
        return value;
      }
    }
  }
  return 0;
}


// Implement
// (DONE)-c Precede each output line with the count of the number of times the line occurred in the input, followed by a single space.
// (DONE)-i Case insensitive comparison of lines.
// -w compare no more than N characters in lines
int main(int argc, char *argv[]) {
  // Reading dictionary john file (john.txt)
  FILE *file = NULL;
  int valueOpW = getOptValue(argc,argv,'w');
  char line[BUFFER_MAX_LENGTH+1];
  int tempChar;
  int lines = 0;
  int tempCharIdx = 0;
  int i=0;



  if (argc >= 2){
       file = fopen(argv[1], "r");
      //  if(hasOpt(argc,argv,'w')==1){
      //    printf("Hast Option w\n");
      //    printf("Value for w is %i\n",valueOpW);
      //  }
      //  if(hasOpt(argc,argv,'c')==1){
      //    printf("Hast Option c\n");
      //  }
      //  if(hasOpt(argc,argv,'i')==1){
      //    printf("Hast Option i\n");
      //  }
  }
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

  char array[lines][BUFFER_MAX_LENGTH+1];
  fseek(file, 0, SEEK_SET);//Reseating file to read again
  i=0;
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
          break;
      }
      else if (tempChar == '\n') {
          line[tempCharIdx] = '\0';
          array[i][tempCharIdx] = '\0';
          i++;
          tempCharIdx = 0;
          continue;
      }
      else{

        if(hasOpt(argc,argv,'i')==1){
          array[i][tempCharIdx] = tolower((char)tempChar);
          line[tempCharIdx++] = tolower((char)tempChar);
        }else{
          array[i][tempCharIdx] = (char)tempChar;
          line[tempCharIdx++] = (char)tempChar;
        }
      }
  }

  //Initial Sort in descending order
  int c,d;
  char swap[BUFFER_MAX_LENGTH + 1];
  for (c = 0 ; c < ( lines - 1 ); c++)
  {
    for (d = 0 ; d < lines - c - 1; d++)
    {

      if (strcmp(array[d],array[d+1])< 0)
      {
        strncpy(swap, array[d], BUFFER_MAX_LENGTH + 1);
        strncpy(array[d], array[d+1], BUFFER_MAX_LENGTH + 1);
        strncpy(array[d+1], swap, BUFFER_MAX_LENGTH + 1);
      }

    }
  }
  // printf("Sorted:\n");
  // normal_output(lines,array);
  // Remove duplicated

  int countRemoved = 0;
  int buffer;
  if(hasOpt(argc,argv,'w')==1){
    buffer = valueOpW;
  }else{
    buffer = BUFFER_MAX_LENGTH + 1;
  }
  char temp[buffer];
  char v1[buffer];
  char v2[buffer];

  for(c=0;c<lines - 1;c++){
    strncpy(v1, array[c],buffer);
    strncpy(v2, array[c+1],buffer);
    if (c>0 && strcmp(v1,temp) == 0){
      strcpy(array[c], "");
      countRemoved++;
      continue;
    }
    if (strcmp(v1,v2) == 0){
      // Empty index
      strcpy(array[c+1], "");
      countRemoved++;
      strncpy(temp, v1,buffer);
    }
  }


  // Create final array
  char tempValue[BUFFER_MAX_LENGTH + 1];
  char finalarray[lines-countRemoved][BUFFER_MAX_LENGTH+1];
  d=1;
  int countDuplicate = 1;
  strncpy(tempValue, array[0],BUFFER_MAX_LENGTH + 1); //Init temp in first
  for(c=0;c<lines;c++){
    if (strcmp(array[c],"") != 0){
      // Add to final string
      strncpy(finalarray[d++], array[c], BUFFER_MAX_LENGTH + 1);
      if(hasOpt(argc,argv,'c')==1 && strcmp(array[c],tempValue) != 0){
        // print word with count
        count_output(countDuplicate, tempValue);
      }
      // save temporal value
      strncpy(tempValue, array[c],BUFFER_MAX_LENGTH + 1);
      //reset counter
      countDuplicate=1;

    }else{
      countDuplicate++;
    }
  }

  // printf("\nFinal\n");
  if(hasOpt(argc,argv,'c')==0){
    normal_output(lines-countRemoved,finalarray);
  }
  return 0;
}
