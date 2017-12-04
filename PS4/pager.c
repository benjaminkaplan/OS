#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv){
  int lineNum = 0;
  char *line;
  size_t size = 0;
  char c = 0;
  FILE *fp;
  if(!(fp = fopen("/dev/tty", "r"))){
    fprintf(stderr, "Error: %s, Errno: %d\n", strerror(errno), errno);
    return -1;
  }

  int j = 0;

  while( (c!=81) && (c!= 113) && (c!= EOF)){
    for(j = 0; j < 23; j++){ 
      if(0 > getline(&line, &size, stdin))
        return 0;
      printf("%s", line);
    }
    printf("--Pess RETURN for more--\n");
    c = fgetc(fp);
   
  }
  if ((c ==81) ||(c==113))
    printf("***Pager terminated by Q***\n");
  return 0;
}
