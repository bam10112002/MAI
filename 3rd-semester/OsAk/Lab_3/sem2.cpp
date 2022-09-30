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

class MySem
{
private:
    int sd;
public:
    enum Msg {CLIENT_GET_MEM, CLIENT_SND_REQUEST, CLIENT_RCV_REPLY, 
              SERVER_RCV_REQUEST, SERVER_SND_REPLY, RESET};
    MySem()
    {
        sd = semget(9,2,IPC_CREAT|0666);
        if (sd == -1){perror("semget: "); exit(-1);}
    }
    void SetSem(int s1,int s2)
    {
        semctl(sd,0,SETVAL,s1);
        semctl(sd,1,SETVAL,s2);
    }
    void GetSem(Msg msg)
    {
        if (msg == Msg::CLIENT_GET_MEM)
        {
            struct sembuf SBuf[2] = {{0,0,0}, {1,-1,0}};
            if (semop(sd, SBuf, 2) == -1){perror("CLIENT_GET_MEM: ");exit(-1);}
        }
        else if (msg == Msg::SERVER_RCV_REQUEST)
        {
            struct sembuf SBuf[2] = {{0,-1,0}, {1,0,0}};
            if (semop(sd, SBuf, 2) == -1){perror("SERVER_GET_MEM: ");exit(-1);}
        }
        else if (msg == Msg::CLIENT_SND_REQUEST)
        {
            struct sembuf SBuf[2] = {{0,1,0}, {1,0,0}};
            if (semop(sd, SBuf, 2) == -1){perror("SERVER_GET_MEM: ");exit(-1);}
        }
        else if (msg == Msg::CLIENT_RCV_REPLY)
        {
            struct sembuf SBuf[2] = {{0,-1,0}, {1,-1,0}};
            if (semop(sd, SBuf, 2) == -1){perror("SERVER_GET_MEM: ");exit(-1);}
        }
        else if (msg == Msg::SERVER_SND_REPLY)
        {
            struct sembuf SBuf[2] = {{0,1,0}, {1,1,0}};
            if (semop(sd, SBuf, 2) == -1){perror("SERVER_GET_MEM: ");exit(-1);}
        }
        else if (msg == Msg::RESET)
        {
            struct sembuf SBuf[2] = {{0,0,0}, {1,1,0}};
            if (semop(sd, SBuf, 2) == -1){perror("SERVER_GET_MEM: ");exit(-1);}
        }

        // switch(msg)
        // {
        //     case Msg::CLIENT_GET_MEM:
        //         struct sembuf SBuf[2] = {{0,0,0}, {1,-1,0}};
        //         if (semop(sd, SBuf, 2) == -1){perror("SERVER_GET_MEM: ");exit(-1);}
        //         break;

        //     case Msg::SERVER_GET_MEM:
        //         struct sembuf SBuf[2] = {{0,-1,0}, {1,0,0}};
        //         if (semop(sd, SBuf, 2) == -1){perror("SERVER_GET_MEM: ");exit(-1);}
        //         break;
        //     case Msg::SND_MSG:
        //         struct sembuf SBuf[2] = {{0,1,0}, {1,0,0}};
        //         if (semop(sd, SBuf, 2) == -1){perror("SERVER_GET_MEM: ");exit(-1);}
        //         break;
            
        // }

    }
};


class MyShMem
{
private:
    int shId;
public:
    MyShMem()
    {
        shId = shmget(10,1024,IPC_CREAT| 0666);
        if (shId == -1)
        {
            cout << "ERROR OPEN SHMGET:" << endl;
            perror("open sh");
        }

    }
    char* GetMem()
    {
        char* ret = (char*)shmat(shId,0,0);
        if (ret == (char*)-1)
        {
            cout << "ERROR IN SHMAT"<<endl;
            perror("shmat");
        }
        return ret;
    }
};

int main()
{

    MySem tmp_sem;
    tmp_sem.SetSem(0,1);
    pid_t pid = fork();
    pid_t pid2;
    // if (pid > 0)
    //     pid2 = fork();


    if (pid > 0) 
    {
        //Сервер
        MySem sem;
        MyShMem sh;
        char* buf;
        int i = 2;

        while(i >= 2)
        {
            buf = sh.GetMem();
            sem.GetSem(MySem::Msg::SERVER_RCV_REQUEST);
            cout << "server started : " << buf << endl;
            strcpy(buf,"World");

            sem.GetSem(MySem::Msg::SERVER_SND_REPLY);
            i--;
            cout << "server wait"<<endl;
        }
        wait(NULL);
    }
    else
    {
        //Клиент
        MySem sem;
        MyShMem sh;
        char* buf;

        sem.GetSem(MySem::Msg::CLIENT_GET_MEM);
        //Посылаем запрос
        cout << "client started" << endl;
        buf = sh.GetMem();
        strcpy(buf,"Hello");

        sem.GetSem(MySem::Msg::CLIENT_SND_REQUEST);

        sem.GetSem(MySem::Msg::CLIENT_RCV_REPLY);
        cout << "RECVEST REPLAY : "<< buf << endl;
        cout << endl;
        sem.GetSem(MySem::Msg::RESET);
    }


    // struct sembuf SBuf[2] = {{0,0,0}, {1,-1,0}};
    // if (semop(sd, SBuf, 2) == -1){perror("semop: "); exit(-1);}
    return 0; 
}