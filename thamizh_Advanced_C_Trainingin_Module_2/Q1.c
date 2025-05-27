#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>
#include<stdlib.h>

bool isPrime(int n)
{
    if (n<=1)
    {
        return false;
    }
    for (int i = 2; i*i <= n; i++)
    {
        if (n%i==0)
        {
            return false;
        }
        
    }
    return true;
    
}



void* primeSum(void* arg)
{
    int sum=0,k=2,count=0;
    int n=*(int*)arg;

    while (count < n)
    {
        if (isPrime(k))
        {
            sum+=k;
            count++;
        }
        k++;
    }
    printf("the sum of first %d prime numbers is %d\n",n,sum);
    return NULL;
}

void* printThread1(void* arg)
{
    int time=0;
    while (time<100)
    {
        printf("Thread 1 running\n");
        sleep(2);
        time+=2;
    }
    return NULL;
    
}

void* printThread2(void* arg)
{
    int time=0;
    while (time<100)
    {
        printf("thread 2 running\n");
        sleep(3);
        time+=3;
    }
    return NULL;
}   

int main()
{
    pthread_t tA,tB,tC;
    int* n = malloc(sizeof(int));
    if (n==NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    

    printf("Enter n\n");
    scanf("%d",n);

    pthread_create(&tA,NULL,primeSum,n);
    pthread_create(&tB,NULL,printThread1,NULL);
    pthread_create(&tC,NULL,printThread2,NULL);

    pthread_join(tA,NULL);
    pthread_join(tB,NULL);
    pthread_join(tC,NULL);

    free(n);
    return 0;
}