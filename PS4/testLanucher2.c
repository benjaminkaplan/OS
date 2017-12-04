#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
  int fd[2];
  pipe(fd);
  pid_t PID1;
  pid_t PID2;
  if((PID = fork())<0){
    perror("fork error");
    return -1;
  }
  if(PID == 0){
    dup2(pipe
  }

  return 0;
}
