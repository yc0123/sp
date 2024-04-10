#include <stdio.h>
#include <pthread.h>

#define LOOPS 100000
int money = 100000;

void *in()
{
  for (int i=0; i<LOOPS; i++) {
    money = money + 1;
  }
  return NULL;
}

void *out()
{
  for (int i=0; i<LOOPS; i++) {
    money = money - 1;
  }
  return NULL;
}


int main() 
{
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, in, NULL);
  pthread_create(&thread2, NULL, out, NULL);

  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
  printf("money=%d\n",money);
}
