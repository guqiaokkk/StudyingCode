#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *thread_funciton(void *arg);

int main()
{
    int res;
    pthread_t a_thread1;
    pthread_t a_thread2;
    void *thread_result;

    res = pthread_create(&a_thread1, NULL, thread_funciton, (void*)"hello thread1");
    if(res != 0)
    {
        perror("Thread creation failed");
        return -1;
    }

    res = pthread_create(&a_thread2, NULL, thread_funciton, (void*)"hello thread2");
    if(res != 0)
    {
        perror("Thread creation failed");
        return -1;
    }

    printf("Waiting for thread to finish..\n");
    res = pthread_join(a_thread1, &thread_result);
    if(res != 0)
    {
        perror("Thread1 join failed");
        return -1;
    }
    printf("Thread1 joined, it returned %s\n", (char*)thread_result);

    res = pthread_join(a_thread2, &thread_result);
    if(res != 0)
    {
        perror("Thread2 join failed");
        return -1;
    }
    printf("Thread2 joined, it returned %s\n", (char*)thread_result);
    return 0;
}

void *thread_funciton(void *arg)
{
    int i = 0;
    for(;i < 10; i++)
    {
        printf("%s\n", (char*)arg);
        sleep(1);
    }
    return NULL;
}