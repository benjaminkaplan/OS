#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAXCHARS 7
int main(int argc, char **argv){
  int numWords = 0;
  if(argc>1)
    numWords = atoi(argv[1]);  
  char *letters[26] = {"A","B","C","D","E", "F", "G", "H", "I", "J", "K", "L",
                    "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W",
                    "X","Y", "Z"};
  int fd;
  int wordsMade = 0;
  srand(time(0));
  do{	
    if(numWords != 0)
      wordsMade++;
    else
      wordsMade--;
    double random = (MAXCHARS+1)*(double)rand()/(double)RAND_MAX;
    int length = (int)random+3; 
    int i = 0;
    char *word = malloc(64);
    int randomInt;
    char* letter;
    for(i = 0; i<length; i++){
      randomInt =  (26)*(double)rand()/(double)RAND_MAX;
      letter = letters[randomInt];
      strcat(word, letter);
    }   
    printf("%s\n", word);

  }while(wordsMade < numWords);

return 0;

}
