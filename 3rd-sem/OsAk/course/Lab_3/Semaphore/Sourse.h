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
#include <string>

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
    void* GetMem()
    {
        void* ret = (void*)shmat(shId,0,0);
        if (ret == (void*)-1)
        {
            cout << "ERROR IN SHMAT"<<endl;
            perror("shmat");
        }
        return ret;
    }
};

class Data
{
public:
    enum class Type {EXPR, ANSWER, ERROR};

    double a,b,rez;
    char op;
    Type type;
    string error;

    Data(double _a, double _b, char _op)
    {
        a = _a;
        b = _b;
        op = _op;
        rez = 0;
        type = Type::EXPR;
    }
    Data(double _rez)
    {
        rez = _rez;
        a = b = op = 0;
        type = Type::ANSWER;
    }
    double GetRez()
    {
        return rez;
    }
    Data(string _error)
    {
        a = b = op = rez = 0;
        error = _error;
        type = Type::ERROR;
    }
};

