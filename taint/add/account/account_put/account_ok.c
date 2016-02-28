#include <pthread.h>
#include <stdio.h>
#include <assert.h>

pthread_mutex_t m;
int nondet_int();
int x, y, z, balance;
int deposit_done=0, withdraw_done=0;

void *deposit(void *arg) 
{
  pthread_mutex_lock(&m);
  balance = balance + y;
  deposit_done=1;
  pthread_mutex_unlock(&m);
}

void *withdraw(void *arg) 
{
  pthread_mutex_lock(&m);
  balance = balance - z;
  withdraw_done=1;
  pthread_mutex_unlock(&m);
}

void *check_result(void *arg) 
{
  int j;
  pthread_mutex_lock(&m);
  if (deposit_done && withdraw_done){
    j=(x + y) - z;
    // assert(balance == j);
  }
  pthread_mutex_unlock(&m);
}

int main() 
{
  pthread_t t1, t2, t3;

  pthread_mutex_init(&m, 0);

  x = 1000;
  y = 100;
  z = 1;
  balance = x;

  pthread_create(&t3, 0, check_result, 0);
  pthread_create(&t1, 0, deposit, 0);
  pthread_create(&t2, 0, withdraw, 0);

  return 0;
}
