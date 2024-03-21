#include<stdio.h>

int power(int a,int n)
{
    if(!n)
    {
        return 1;
    }
    else if(n==1)
    {
        return a;
    }
    else
    {
        return a*power(a,n=n-1);
    }
}

int main()
{
    printf("power(5,3)=%d\n",power(5,3));
}