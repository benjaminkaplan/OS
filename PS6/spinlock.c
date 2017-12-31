#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "spinlock.h"
#include <stdlib.h>



void spin_lock(struct spinlock *l){
  while(tas(l->lock) != 0)
    sched_yield();
  l->lock = 1;
  l->holder = getpid();

}

void spin_unlock(struct spinlock *l){
  l->lock = 0;
}


