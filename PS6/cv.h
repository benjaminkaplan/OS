#ifndef CV_H_
#define CV_H_
#include <unistd.h>
#define CV_MAXPROC 65
struct cv{
  pid_t waiters[CV_MAXPROC];
  int num_waiters;
  pid_t sleeping_caller;
  struct spinlock lock;
};

void cv_init(struct cv *cv);

void cv_wait(struct cv *cv, struct spinlock *mutex);

int cv_boradcast(struct cv *cv);

int cv_signal(struct cv *cv);

#endif
