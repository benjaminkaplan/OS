#include "fifo.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void fifo_init(struct fifo *f){
  //fifo->lock->lock = 0;
  fifo->full = cv_init(&fifo->full);
  fifo->full=cv_init(&fifo->empty);
  fifo->next_write = 0;
  fifo->next_read = 0;
  fifo->item_count = 0;
}

void fifo_wr(struct fifo *f, unsigned long d){
  spin_lock(&fifo->lock);
  while(fifo->item_count >= MYFIFO_SIZE)
    cv_wait(&fifo->full, &fifo->lock);
  fifo->buf[fifo->next_write++] = d;
  fifo->next_write %=MYFIFO_SIZE;
  fifo->item_count++;
  cv_signal(&fifo-> empty);
  spin_unlock(&fifo_lock);
}

unsigned long fifo_rd(struct fifo *f){
  unsigned long d;
  spin_lock(&fifo->lock);
  while(&fifo->item_count<=0)
    cv_wait(&fifo->empty, &fifo->lock);
  d = fifo->buf[fifo->next_read++];
  fifo->next_read %= MYFIFO_SIZE;
  fifo->item_count--;
  cv_signal(&fifo->full);
  spin_unlock(&fifo->lock);
  return d;
}



