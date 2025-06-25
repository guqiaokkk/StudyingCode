#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#define SHM_PATH "/mnt/hgfs/shared/TestShm"
#define STUDENT_NUM 3

struct Student {
    int iNO;       // 学号
    char sName[20]; // 姓名
    char cSex;     // 性别
    int iAge;      // 年龄
    char sAddr[100]; // 地址
};

int Init(struct Student arr[]) {
    for (int i = 0; i < STUDENT_NUM; i++) {
        arr[i].iNO = i;
        sprintf(arr[i].sName, "TOM%d", i);
        arr[i].cSex = 'M';
        arr[i].iAge = i * 10;
        sprintf(arr[i].sAddr, "Nanjing, Jiangsu, China%d", i);
    }
    return 0;
}

int WriteData(struct Student arr[]) {
    int iRet = 0;
    unsigned nMemSize = sizeof(struct Student) * STUDENT_NUM;
    void *pAddr = NULL;
    int iShm_id = 0;

    key_t key = ftok(SHM_PATH, 0);
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    iShm_id = shmget(key, nMemSize, 0660 | IPC_CREAT);
    if (iShm_id == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    printf("key : iShmID = %d:%d\n", key, iShm_id);

    pAddr = shmat(iShm_id, NULL, 0);
    if (pAddr == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    struct Student *pTmp = (struct Student *)pAddr;
    for (int i = 0; i < STUDENT_NUM; i++) {
        pTmp->iNO = arr[i].iNO;
        pTmp->iAge = arr[i].iAge;
        pTmp->cSex = arr[i].cSex;
        strcpy(pTmp->sName, arr[i].sName);
        strcpy(pTmp->sAddr, arr[i].sAddr);
        pTmp++;
    }

    pTmp = (struct Student *)pAddr;
    for (int i = 0; i < STUDENT_NUM; i++) {
        printf("Student %d:\nNO:%d\nNAME:%s\nSEX:%c\nAGE:%d\nADDR:%s\n\n",
               i, arr[i].iNO, arr[i].sName, arr[i].cSex, arr[i].iAge, arr[i].sAddr);
    }

    if (shmdt(pAddr) != 0) {
        perror("shmdt failed");
        return -1;
    }

    return 0;
}

int ReadData(int iShmID) {
    struct Student *pAddr = (struct Student *)shmat(iShmID, NULL, 0);
    if (pAddr == (struct Student *)-1) {
        perror("shmat failed");
        return -1;
    }

    for (int i = 0; i < STUDENT_NUM; i++) {
        printf("Student %d:\nNO:%d\nNAME:%s\nSEX:%c\nAGE:%d\nADDR:%s\n\n",
               i, (pAddr + i)->iNO, (pAddr + i)->sName, (pAddr + i)->cSex, (pAddr + i)->iAge, (pAddr + i)->sAddr);
    }

    if (shmdt(pAddr) != 0) {
        perror("shmdt failed");
        return -1;
    }

    return 0;
}

int DestroyMem(int iShmID) {
    if (shmctl(iShmID, IPC_RMID, NULL) != 0) {
        perror("shmctl failed");
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int iOperType = 1;
    int iShmID = 0;

    if (argc != 3) {
        printf("Invalid input.\n");
        return -1;
    }

    iOperType = atoi(argv[1]);
    iShmID = atoi(argv[2]);

    printf("OperType = %d, iShmID = %d\n", iOperType, iShmID);

    struct Student tStudents[STUDENT_NUM];
    Init(tStudents);

    if (iOperType == 1) {
        WriteData(tStudents);
    } else if (iOperType == 2) {
        ReadData(iShmID);
    } else if (iOperType == 3) {
        DestroyMem(iShmID);
    } else {
        printf("Invalid operation type.\n");
        return -1;
    }

    return 0;
}