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
  char letter = 'A';
  for(j=0; j< 5000; j++){
    if(write(fd, &letter, 1)<0){
      perror("Write error: ");
      exit(EXIT_FAILURE);
    }
  }
  struct stat statbuf1;
  if(fstat(fd, &statbuf1)<0){
    perror("Stat error1: ");
    exit(EXIT_FAILURE);
  }

  if(lseek(fd, 0, SEEK_END)<0){
    perror("MMAP error: ");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr,"statbuf1 size: %d\n", (int)statbuf1.st_size);
  char * memory;
  if((memory = mmap(NULL, 1, PROT_WRITE| PROT_READ, MAP_SHARED, fd,0 ))<0){
    perror("MMAP error: ");
    exit(EXIT_FAILURE);
  }
  *(memory+5001) = 'A';

  struct stat statbuf2;
  if(fstat(fd, &statbuf2)<0){
    perror("Stat error2: ");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr,"statbuf2 size: %d\n", (int) statbuf2.st_size);
  int size1 = (int) statbuf1.st_size;
  int size2 = (int) statbuf2.st_size;
  if(size1 == size2)
    return 1;
  return 0;
  
} 
