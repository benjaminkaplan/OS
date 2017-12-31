#ifndef FIFO_H_
#define FIFO_H_
#include "spinlock.h"
#define MYFIFO_SIZE 1024
struct fifo{
  struct spinlock lock;
  struct cv full, empty;  
  unsigned long buf[MYFIFO_SIZE];
  int next_write, next_read;
  int item_count;
}fifo;

void fifo_init(struct fifo *f);
void fifo_wr(struct fifo *f, unsigned long d);
unsigned long fifo_rd(struct fifo *f);



#endif
