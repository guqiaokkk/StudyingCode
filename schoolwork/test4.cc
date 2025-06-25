#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int count = 0;
pthread_mutex_t lock;
void *pthread_run(void *arg)
{
    int i = 0;  
    int ret = 0;
    while (i < 50)
    {
        pthread_mutex_lock(&lock);
        i++;
        ret = count;
        printf("process ID: %d,pthread ID:%lu, count:%d\n", getpid(), pthread_self(), count);
        count = ret + 1;
        pthread_mutex_unlock(&lock);
        usleep(100);
    }
    return NULL;
}

int main()
{
    int ret = 0;
    pthread_mutex_init(&lock, NULL);
    pthread_t id1;
    pthread_t id2;
    pthread_create(&id1, NULL, &pthread_run, NULL);
    pthread_create(&id2, NULL, &pthread_run, NULL);
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    printf("count: %d\n", count);

    pthread_mutex_destroy(&lock);
    return 0;
}