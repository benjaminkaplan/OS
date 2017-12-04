#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <setjmp.h>
#include <sys/signal.h>
int numMatched = 0;

void pipe_handler(int sn){
  printf("%d words matched\n", numMatched);  
}


int main(int argc, char **argv){
  signal(SIGPIPE, &pipe_handler);
  
  if(argc !=2){
    fprintf(stderr, "Error: Wrong number of arguments\n");
    return -1;
  }
  

  char *word = NULL;  
  FILE *fp;
  if( !(fp = fopen(argv[1], "r")))
    fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errno), errno);
  size_t size = 0;
  char *input = NULL;
//  getline(&input, &size, stdin);
  
  int num = 370098 * sizeof(char*);
  int matched = 0;
  
  int z = 0;
  //getline(&input, &size, stdin);
//  printf("INPUT  = %s\n", input);
  int a = 0;
  while(0<(a = getline(&input, &size, stdin))){
    //printf("INPUT  = %s\n", input);
    for(z = 0; z<370098; z++){
      getline(&word, &size, fp);
//      printf("%s\n", word);
      if ( !strncmp(input, word, strlen(input) -1)){
        matched =1;        
      }
    }
    rewind(fp);
    if( matched == 1){
      matched =0;
      printf("%s", input);
      numMatched++;
//      printf("Matched #%d\n", numMatched);
    }
    //getline(&input, &size, stdin);
//    printf("New Line retrieved: %s\n", input);    
  }
  printf("%d words matched\n", numMatched);

  return 0;
}
