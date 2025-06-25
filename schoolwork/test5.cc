#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <mutex>

std::mutex _mutex;


void *printer(char *str)
{
    std::unique_lock<std::mutex> _lock(_mutex);
    while (*str != '\0')
    {
        putchar(*str);
        fflush(stdout);
        str++;
        sleep(1);
    }
    printf("\n");
}

void *thread1_fun(void *arg)
{
    char *str = "HELLO";
    printer(str);
}

void *thread2_fun(void *arg)
{
    char *str = "WORLD";
    printer(str);
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread1_fun, NULL);
    pthread_create(&tid2, NULL, thread2_fun, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    return 0;
}