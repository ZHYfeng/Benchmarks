#include <pthread.h>
#include <stdio.h>
#include <assert.h>

#define SIZE	(4)
#define EMPTY	(-1)
#define FULL	(-2)
#define FALSE	(0)
#define TRUE	(1)

typedef struct {
  int element[SIZE];
  int head;
  int tail;
  int amount;
} QType;

pthread_mutex_t m;
int stored_elements[SIZE];
int enqueue_flag, dequeue_flag;
QType queue;

int init(QType *q) 
{
  q->head=0;
  q->tail=0;
  q->amount=0;
}

int empty(QType * q) 
{
  if (q->head == q->tail) 
  { 
    printf("queue is empty\n");
    return EMPTY;
  }
  else 
    return 0;
}

int full(QType * q) 
{
  if (q->amount == SIZE) 
  {  
    printf("queue is full\n");
    return FULL;
  } 
  else
    return 0;
}

int enqueue(QType *q, int x) 
{
  q->element[q->tail] = x;

  q->amount++;
  if (q->tail == SIZE) 
  {
    q->tail = 1;
  } 
  else 
  {
    q->tail++;
  }

  return 0;
}

int dequeue(QType *q) 
{
  int x;

  x = q->element[q->head];
  q->amount--;
  if (q->head == SIZE) 
  {
    q->head = 1;
  } 
  else 
    q->head++;

  return x;
}

void *t1(void *arg) 
{
  int value, i;

  pthread_mutex_lock(&m);
  if (enqueue_flag)
  {
    queue.amount=queue.amount;
    make_taint(&(queue.amount));
    for(i=0; i<SIZE; i++)  
    {
      value = 8;
      enqueue(&queue,value);
      stored_elements[i]=value;
    }
    enqueue_flag=FALSE;
    dequeue_flag=TRUE;
  }	
  pthread_mutex_unlock(&m);

  return NULL;
}

void *t2(void *arg) 
{
  int i;
  int j;

  pthread_mutex_lock(&m);
  if (dequeue_flag)
  {

    for(i=0; i<SIZE; i++)  
    {
      if (empty(&queue)!=EMPTY){
        j=dequeue(&queue);
        // assert(j==stored_elements[i]);
      }
    }
    dequeue_flag=FALSE;
    enqueue_flag=TRUE;
  }
  pthread_mutex_unlock(&m);

  return NULL;
}

int main(void) 
{
  int j;
  pthread_t id1, id2;

  enqueue_flag=TRUE;
  dequeue_flag=FALSE;

  init(&queue);

  j=empty(&queue);
  // assert(j==EMPTY);

  pthread_mutex_init(&m, 0);

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  return 0;
}

