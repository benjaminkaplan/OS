#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "spinlock.h"


void failure(int errnum){
  fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errnum), errnum);
  exit(EXIT_FAILURE);
}


int main(int argc, char **argv){
  struct spinlock lock;
  lock.lock = 0;
  if(argv[1] ==NULL || argv[2] == NULL){
    fprintf(stderr, "Missing options!\n");
    exit(EXIT_FAILURE);
  }
  int *memory = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED,-1,0);
  
  if(memory == NULL)
    failure(errno);
  //*memory +=1;
  int status = 0;
  int nchild = atoi(argv[1]);
  int niter = atoi(argv[2]);
  int i = 0;
  int j = 0;
  pid_t PID, wpid;
  for(i=0; i<nchild; i++){
    if((PID = fork())<0)
      failure(errno);
    if(PID == 0){
      fprintf(stderr,"in child %d\n", i);
      for(j = 0; j<niter; j++){
        fprintf(stderr,"THIS IS CHILD #%d speaking, iteration #%d\n", i,j);
        spin_lock(&lock);
        perror("lock attained\n");
        *memory+=1;
        spin_unlock(&lock);
      }
      return 0;
    }
    
 
  }
   while ((wpid = wait(&status)) > 0);
   printf("memory = %d\n", *memory); 
 return 0;
}
