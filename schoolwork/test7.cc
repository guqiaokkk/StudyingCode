#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<error.h>
#include <time.h>
#define SHM_PATH "/mnt/hgfs/shared/TestShm4"
int main(){
int shm_id=-1;
int *share;
int num;
srand(time(NULL));
key_t key =ftok(SHM_PATH, 0);
shm_id = shmget(key,64,0666|IPC_CREAT);
printf("key :iShmID = %d:%d\n",key, shm_id);
//printf("errno:%d",errno);
perror("shmget:");
if(shm_id == -1){
perror("shmget()");
}
share = (int *)shmat(shm_id, 0, 0);
perror("shmat:");
while(1){
num = random() % 1000;
*share = num;
printf("write a random number %d\n", num);
sleep(1);
}
return 0;
}