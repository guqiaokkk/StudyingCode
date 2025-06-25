#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int count = 0;

void *pthread_run(void *arg)
{
    int i = 0;
    int iRet = 0;
    while (i < 50)
    {
        i++;
        iRet = count;
        printf("pthread ID:%lu, count: %d\n", pthread_self(), count);

        count = iRet + 1;
        usleep(1000);
    }
    return NULL;
}

int main()
{
    int ret = 0;
    pthread_t id1;
    pthread_t id2;
    pthread_create(&id1, NULL, &pthread_run, NULL);
    pthread_create(&id2, NULL, &pthread_run, NULL);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    printf("count: %d\n", count);
    return 0;
}