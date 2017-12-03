
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
int main(int argc, char ** argv){
  int fd;
  
  if( (fd = open("testfile.txt", O_RDWR | O_CREAT |O_TRUNC, 0666))<0){
    perror("Open error: ");
    exit(EXIT_FAILURE);
  }
  
  write(fd, "Hello world", 5);//This is necessary because you will 
                              //get a SIGBUS if you attempt to write to the
                              //MMAPing of a file with 0 bytes size
  
  char *memory = malloc(10);
  if((memory = mmap(NULL, 4096,  PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))<0){
    perror("MMAP error: ");
    exit(EXIT_FAILURE);
  }
  char letter = 'A';

  *memory = 'A';

  int g;
  if((g = lseek(fd, 0, SEEK_SET))<0){
    perror("Seek error: ");
    exit (EXIT_FAILURE);
  } 


  char* buf;
  if((buf = malloc(10)) <0){
    perror("Malloc error: ");
    exit(EXIT_FAILURE);
  }
  if(read(fd,buf, 1) <0){
    perror("Read error: ");
    exit(EXIT_FAILURE);
  }
  fprintf(stderr,"%s\n", buf); 
  if(close(fd)<0){
    perror("closing error: ");
    exit(EXIT_FAILURE);
  }
  if(!strcmp("A", buf))
    return 0;
  return 1;
  
}
