#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<signal.h>

volatile __sig_atomic_t runStatus=1;


void handle_signal(int sig)
{
    printf("You terminated the program, so stopping gracefully\n");
    runStatus=0;
}

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
    time_t start=time(NULL);
    int sum=0,k=2,count=0;
    int n=*(int*)arg;

    while (count < n)
    {
        if(!runStatus) break;
        if (isPrime(k))
        {
            sum+=k;
            count++;
        }
        k++;
    }
    printf("the sum of first %d prime numbers is %d\n",n,sum);
    time_t end=time(NULL);
    printf("Thread A ran %ld s\n",end-start);
    return NULL;
}

void* printThread1(void* arg)
{
    time_t start=time(NULL);
    int times=0;
    while (times<100 && runStatus)
    {
        printf("Thread 1 running\n");
        sleep(2);
        times+=2;
    }
    time_t end= time(NULL);
    printf("Thread 1 ran %ld s\n",end-start);
    return NULL;
    
}

void* printThread2(void* arg)
{
    time_t start=time(NULL);
    int times=0;
    while (times<100 && runStatus)
    {
        printf("thread 2 running\n");
        sleep(3);
        times+=3;
    }
    time_t end=time(NULL);
    printf("Thread 2 ran %ld s\n",end-start);
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
    signal(SIGINT,handle_signal);

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