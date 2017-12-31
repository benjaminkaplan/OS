#include <errno.h>
#include <string.h>
#include "cv.h"
#include <signal.h>
#include "spinlock.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "fifo.h"
#include <sys/mman.h>

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
  
  char * memory = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
  if(memory == NULL){
    fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errno), errno);
    exit(EXIT_FAILURE);
  }
  struct fifo fifo1;
  memory = fifo1;
  fifo_init(&fifo1);
  pid_t child1;
  pid_t child2;
  int k = 0;
  //for(k = 0; k<2; k++){
    if((child1 = fork())<0){
      fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errno), errno);
      return -1;
    }
    if(child1 ==0){//CHILD1 - WRITE
      int l = 0;
      for(l = 0; l< 2048; l++){
        fifo_wr(&fifo1, l);
      }
      
    }
    else{// PARENT
      if((child2 = fork())<0){
      fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errno), errno);
      return -1;
      }
      if(child2 ==0){//CHILD2 - READ
        fprintf(stderr, "%li\n", fifo_rd(&fifo1));
      }
      else  //Parent
        ;
        
    }
  //}
    
}
