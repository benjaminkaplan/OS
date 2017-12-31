#include <errno.h>
#include <string.h>
#include "cv.h"
#include <signal.h>
#include "spinlock.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void sigusr1_handler(int signo){
  ;
}
int main(int argc, char **argv){
  if(argv[1] == NULL){
    fprintf(stderr, "missing arguments!\n");
    return -1;
  }
  int num = atoi(argv[1]);
  if(0> signal( SIGUSR1, sigusr1_handler)){
    fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errno), errno);
    exit(EXIT_FAILURE);
  }
  
  char * memory = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0)
  if(memory == NULL){
    fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errno), errno);
    exit(EXIT_FAILURE);
  }
  pid_t child;
  int k = 0;
  for(k = 0; k<num; k++){
    if((child = fork())<0){
      fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errno), errno);
      return -1;
    }
    if(child ==0){//CHILD

      break;
    }
    else{// PARENT
    
    }
  }
  



  return 0;
}
