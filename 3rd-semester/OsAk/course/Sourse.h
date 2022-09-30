#include <iostream>
#include <string>
#include <cstdio>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <random>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>


//Semaphor include
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

#define MSG_MAX 1024
#define MSG_ID 15

#define PORT 3008

using namespace std;

enum class ValType { NONE, DISTANCE, WEIGHT, SQUARE };
enum class NSType {NONE, OLDRUSSIAN,  BRITISH, SI};
enum class Type { SEM, MSG};

class Value
{
public:
    double data;
    ValType vType;
    NSType ns;
    Value(){ data =0; vType = ValType::NONE; ns = NSType::NONE;}
};






struct mbuf 
{
    long mtype;
    char mtext[MSG_MAX];
};
typedef struct mbuf MBuf;

class Msg
{
public:
    Value val;
    NSType targetNS;

    Msg(){}
    Msg(Value _val, NSType target)
    {
        val = _val;
        targetNS = target;
    }
};

int msgSend(int md, MBuf* buf)
{
    if (msgsnd(md, buf, MSG_MAX, IPC_NOWAIT))
    {
        perror("msgsnd error: ");
        cout << "try open MsgQ"<< endl;
        md = msgget(MSG_ID,IPC_CREAT | 0666);   // открываем очередь
        if (md == -1){ perror("create MSG queue error: "); exit(-1);}

        if (msgsnd(md, buf, MSG_MAX, IPC_NOWAIT)){ perror("msgsnd error: "); exit(-1); }
        cout << "msg send"<<endl;
    }
    return md;
}
int msgRcv(int md, MBuf* buf, int type)
{
    if (msgrcv(md, buf, MSG_MAX, type, 0) == -1)
    {
        perror("msgrcv error: ");
        cout << "try open MsgQ"<< endl;
        md = msgget(MSG_ID,IPC_CREAT | 0666);   // открываем очередь
        if (md == -1){ perror("create MSG queue error: "); exit(-1);}

        if (msgrcv(md, buf, MSG_MAX, type, 0) == -1){ perror("msgrcv error: "); exit(-1); }
        cout << "msg rcv"<<endl;
    }
    return md;
}





//Semaphor

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
    void printSem()
    {
        cout << semctl(sd, 0, GETVAL,0) << " "<< semctl(sd, 1, GETVAL,0) << endl;
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
