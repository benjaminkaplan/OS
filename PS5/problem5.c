#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char **argv){
  int fd;
  if((fd = open("testfile.txt", O_RDWR|O_CREAT|O_TRUNC, 0666))<0){
    perror("Write error: ");
    exit(EXIT_FAILURE);
  }

  int j= 0;
  char letterA = 'A';
  for(j=0; j< 5000; j++){
    if(write(fd, &letterA, 1)<0){
      perror("Write error: ");
      exit(EXIT_FAILURE);
    }
  }
  if(lseek(fd, 0, SEEK_END)<0){ // lseeks to end of file
    perror("Lseek error: ");
    exit(EXIT_FAILURE);
  }
  char *memory;
  if(!(memory = mmap(NULL, 8192, PROT_READ|PROT_WRITE,MAP_SHARED,fd,0))){
    perror("MMAP error: ");
    exit(EXIT_FAILURE);
  }
  char letterB = 'B';
  int posX;
  *(memory+5000) = 'B';
  
  if((posX = lseek(fd,0,SEEK_CUR))<0){
    perror("Lseek error: ");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr, "posX =  %d\n", posX);
  int g;
  if((g =lseek(fd, 16, SEEK_END))<0){
    perror("Lseek error: ");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr,"lseek to: %d\n", g);
  char letterC = 'C';
  if(write(fd, &letterC, 1)<0){
    perror("Write error: ");
    exit(EXIT_FAILURE);
  }
  char *buf;
  if(lseek(fd, posX, SEEK_SET)<0){
    perror("lseek error:");
    exit(EXIT_FAILURE);
  }
  if((buf = malloc(10))<0){
    perror("malloc:");
    exit(EXIT_FAILURE);
  }
  if(read(fd, buf, 1)<0){
    perror("read:");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr,"buf = %s\n", buf);
  if(!strcmp(buf,"B"))
    return 0;
  return 1; 
}
