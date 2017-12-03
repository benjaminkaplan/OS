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

int main(int argc, char **argv){
  void sigHand(int signo){
    fprintf(stderr, "Signal recieved: %d\n", signo);
    exit(signo);
  }

  int j = 0;
  for(j = 1; j<32; j++){
    if (signal(j, sigHand) == SIG_ERR)
      fprintf(stderr,"cannot handle signal: %d\n", j);
  }
  
  int fd;
  if((fd = open("testfile6.txt", O_RDWR|O_TRUNC|O_CREAT, 0666))<0){
    perror("Write error: ");
    exit(EXIT_FAILURE);
  }
  int k = 0;
  char letterA = 'A';
  for(k=0; k<1000; k++){
    if(write(fd, &letterA, 1)<0){
      perror("Write error: ");
      exit(EXIT_FAILURE);
    }
  }

  char * memory;
  if((memory = mmap(NULL, 8192, PROT_WRITE| PROT_READ, MAP_PRIVATE, fd, 0))<0){
    perror("MMAP error: ");
    exit(EXIT_FAILURE);
  }

  char* buf;
  char char1 = *(memory+1500);

  fprintf(stderr,"Read 1 succeeded past end of file.\n Byte read: %c\tASCII code:%d\n", char1,char1);

  char char2 = *(memory + 5000);

  fprintf(stderr,"Read 2 succeeded past end of file.\n Byte read: %c\tASCII code:%d\n", char2,char2);

  return 0;
}
