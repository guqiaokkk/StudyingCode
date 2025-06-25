#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>

int main()
{
    int pid;
    int fd[2];
    char S[20];
    pipe(fd);
    pid = fork();
    if(pid == 0)
    {
        int i = 0;
        for(; i < 10; i++)
        {
            snprintf(S, sizeof(S),"Hello, No %d\n", i);
            write(fd[1], S, 20);
            sleep(1);
        }
        exit(0);
    }
    else
    {
        int i = 0;
        for(; i < 10; i++)
        {
            read(fd[0], S, 20);
            printf("%s", S);
            sleep(1);
        }
        exit(0);
    }
    return 0;
}