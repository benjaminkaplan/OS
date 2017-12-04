#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char ** argv){
  void sigHand(int signo){
    fprintf(stderr, "Signal recieved: %d\n", signo);
    exit(signo);
  }
  int j = 1;
  for(j = 1; j<32; j++){
    if (signal(j, sigHand) == SIG_ERR)
      fprintf(stderr,"cannot handle signal: %d\n", j);
  }
  int fd;
  if((fd = open("testfile1.txt", O_RDWR|O_TRUNC|O_CREAT, 0666))<0){
    perror("Write error: ");
    exit(EXIT_FAILURE);
  }
  if(write(fd,"Hello world", 11)<0){
    perror("write error: ");
    exit(EXIT_FAILURE);
  }
  char *memory;
  if((memory = mmap(NULL, 11, PROT_READ, MAP_SHARED,fd,0))<0){
    perror("Mmap error: ");
    exit(EXIT_FAILURE);
  }

  *memory = 'A';
  if(*memory == 'H'){
    exit(255);
  }

  return 0;
}
