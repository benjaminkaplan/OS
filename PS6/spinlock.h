#ifndef SPINLOCK_H_
#define SPINLOCK_H_
struct spinlock {
  char *lock;
  int holder;
  int numlock;
};

int tas(volatile char *lock);
    

void spin_lock(struct spinlock *l);

void spin_unlock(struct spinlock *l);

#endif

