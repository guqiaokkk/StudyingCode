#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>

#define SHM_PATH "/mnt/hgfs"

struct mt
{
   int num;
   pthread_mutex_t mutex;
   pthread_mutexattr_t mutexattr;
};

int main ()
{
    int iRet=0;
	unsigned nMemSize=sizeof(struct mt);
	struct mt *pMt;
	int iShm_id=0;
	key_t key =ftok(SHM_PATH, 0);

	iShm_id=shmget(key,nMemSize,0660|IPC_CREAT);

	printf("key :iShmID = %d:%d\n",key, iShm_id);
	if(iShm_id<0)
	{
		iRet=-1;
		perror("shmget failed\n");
		return iRet;
	}

    pMt = (struct mt*)shmat(iShm_id, NULL, 0);
	if (pMt == nullptr)
	{
		perror("shmat addr error\n");
		return -1;
	}

    pMt->num=0;
    pthread_mutexattr_init(&pMt->mutexattr);                                  //初始化mutex属性对象
    pthread_mutexattr_setpshared(&pMt->mutexattr, PTHREAD_PROCESS_SHARED);    //修改属性为进程间共享
    pthread_mutex_init(&pMt->mutex, &pMt->mutexattr);                          //初始化一把mutex琐

	pid_t child_pid;
	printf ("the main program process ID is %d\n", (int) getpid ());

	child_pid = fork ();
	if (child_pid != 0)
	{
	    int i=0;
            int iTmp=0;
	    for (i = 0; i < 100; i++)
	    {
           pthread_mutex_lock(&pMt->mutex);
           iTmp=(pMt->num);
           printf("-parent----num++   %d\n", pMt->num);
           pMt->num=iTmp+1;
          pthread_mutex_unlock(&pMt->mutex);
           usleep(1000);
        }
        if (0!= shmdt((void*)pMt))
	    {
		 perror("shmdt addr error\n");
		 return -1;
        }
	}
	else
	{
	    int i=0;
      int iTmp=0;
	    for (i = 0; i < 100; i++)
	    {
           pthread_mutex_lock(&pMt->mutex);
           iTmp=(pMt->num);
           printf("*******************child----num++   %d\n", pMt->num);
           pMt->num=iTmp+1;
          pthread_mutex_unlock(&pMt->mutex);
           usleep(1000);
        }
        if (0!= shmdt((void*)pMt))
	    {
		   perror("shmdt addr error\n");
		   return -1;
      }
	}
	return 0;
}
