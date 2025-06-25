#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<error.h>
#define SHM_PATH "/mnt/hgfs/shared/TestShm4"
int main(){
int shm_id;
int *share;
key_t key =ftok(SHM_PATH, 0);
shm_id = shmget (key, 0, 0660);
if(shm_id == -1){
perror("shmget()");
}
share = (int *)shmat(shm_id, 0, 0);
while(1){
sleep(1);
printf("%d\n", *share);
}
return 0;
}