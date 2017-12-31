#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include "cv.h"
#include "spinlock.h"
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

void cv_init(struct cv *cv){
  
  cv->num_waiters = 0;
  cv->sleeping_caller = 0;
}

void cv_wait(struct cv *cv, struct spinlock *mutex){
  cv->sleeping_caller = getpid();
  spin_unlock(mutex);
  sigset_t set;
  sigfillset(&set);  
  sigsuspend(&set);
}

int cv_broadcast(struct cv *cv){
  int j = 0;
  int awoken = 0;
  for(j= 0 ; j<cv->num_waiters; j++){
    if(kill(cv->waiters[j], SIGUSR1) <0)
      fprintf(stderr, "Error %s, Errno: %d\n", strerror(errno), errno);
    awoken++;
  }
  return awoken; 
}

int cv_signal(struct cv *cv){
  int sig;
  while(kill(cv->waiters[sig], SIGUSR1)<0){
    fprintf(stderr, "Error: Unable to signal - %s, Errno: %d\n", strerror(errno), errno);
    sig++;                //if first process cannot be signaled, 
                          //then next process is chosen
    if(sig > numwaiters){ //if the end of the list is reached,
      sig = 0;            //it will start again. This may end up in an endless loop,
    }                     //but this is unlikely. More likely that some process will act
  }
  return 1;
}                           
