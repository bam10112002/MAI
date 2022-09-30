#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cmath>

#include <iostream>
#include <string>
#include <cstdio>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include <sys/shm.h>

using namespace std;


// struct sembuf genSemBuf(int first, int second)
// {
//     struct sembuf sbuf[2];
//     sbuf->sem_num = 0;
//     sbuf->sem_op = first;
//     sbuf->sem_flg = 0;

//     sbuf->sem_num = 1;
//     sbuf->sem_op = second;
//     sbuf->sem_flg = 0;

//     return sbuf;
// }

int main()
{

    cout << ".";
    struct sembuf sbuf[2] = {{0,0,0}, {1,1,0}};
    int sem = semget(9,2,IPC_CREAT | 0666);
    int sh = shmget(11,1024,IPC_CREAT | 0666);
    if (sem == -1){ perror("semget: "); exit(-1); }
    if (sh == -1){ perror("shmget: "); exit(-1); }

    if (semop(sem, sbuf, 2) == -1){ perror("semop: "); exit(-1); }
    struct sembuf sbufx[2] = {{0,-1,0}, {1,0,0}};
    semop(sem, sbufx, 2);
    int pid = fork();

    if (pid > 0)
    {
        // Сервер
        cout <<"Server" << endl;
        sem = semget(9,2,IPC_CREAT | 0666);
        sh = shmget(11,1024,IPC_CREAT | 0666);
        
        while(1){
        struct sembuf sbuf1[2] = {{0,-1,0}, {1,0,0}};
        if (semop(sem, sbuf1, 2) == -1){ perror("semop_1: "); exit(-1); }

        cout << "Server worked"<<endl;

        struct sembuf sbuf2[2] = {{0,1,0}, {1,1,0}};
        if (semop(sem, sbuf2, 2) == -1){ perror("semop_5: "); exit(-1); }
        cout << "sbuf = " << sbuf2[0].sem_op << "||" <<sbuf2[1].sem_op  << endl;
        }

    }
    else
    {
        // Клиент
        cout <<"Client" << endl;

        sem = semget(9,2,IPC_CREAT | 0666);
        sh = shmget(11,1024,IPC_CREAT | 0666);

        while(1){
        struct sembuf sbuf2[2] = {{0,0,0}, {1,-1,0}};
        cout << "client wait" << endl;
        if (semop(sem, sbuf2, 2) == -1){ perror("semop_2: "); exit(-1); }

        cout << "Client worked" << endl;

        struct sembuf sbuf3[2] = {{0,1,0}, {1,0,0}};
        if (semop(sem, sbuf3, 2) == -1){ perror("semop_3: "); exit(-1); }
        }
    }



    return 0; 
}