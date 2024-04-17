#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main()
{ 
  if (fork()==0) 
  {
    if(fork()==0)
    {
      while (1)
      {
        printf("George\n");
        sleep(1);
      }
    }
    else
    {
      while (1)
      {
        printf("Mary\n");
        sleep(2);
      }
    }
  } 
  else 
  {
    while (1)
    {
      printf("----------------\n");
      sleep(1);
    }
  }
}