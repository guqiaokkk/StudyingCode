#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>

void func(int a);
int main()
{
    int i,j;
    signal(17, func);
    int iPID = fork();
    if(iPID > 0)
    {
        printf("PID: %d, Parent: Signal 17 will be send to Child!\n", getpid());
        kill(iPID, 17);

        printf("PID: %d, Parent: finished!\n", getpid()); 
    }
    else
    {
        printf("PID: %d\n", getpid()); 
        sleep(1);
        printf("PID: %d, Child: finished!\n", getpid()); 
        exit(0);
    }
    return 0;
}

void func(int a)
{
    printf("PID: %d, It is Signal 17 processing function \n", getpid());
}