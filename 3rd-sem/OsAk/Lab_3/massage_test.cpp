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

# define MSG_MAX 1024
using namespace std;

// void firstTest()
// {
    // strcpy (mobj.mtext, "Hello");
    // mobj.mtype = 15;
    // int pid = fork();
    // int fd; 

    // if (pid > 0)
    // {
    //     // Server
    //     fd = msgget(15,IPC_CREAT | 0666);  
    //     //отправка 
    //     if (fd == -1 || msgsnd(fd,&mobj, strlen(mobj.mtext) + 1, IPC_NOWAIT != 0))
    //     {
    //         cout << "fd = "  << fd << endl;
    //         perror("masage");
    //         exit(-1);
    //     } 
    //     wait(NULL);
    //     int rc = msgctl(fd, IPC_RMID,0);
    //     if (rc == -1){ perror("masgctl");}
    // }
    // else
    // {
    //     //Client
    //     fd = msgget(15,IPC_CREAT | 0666);
    //     // прием сообщения
    //     if (msgrcv(fd, &mobj, MSG_MAX , 0 ,  0) == 0);
    //     {
    //         cout << "new massage: " <<mobj.mtext << endl;
    //     }
    // }
// }


void cubic(double a,double b, double c,double d, double& _x1, double& _x2, double& _x3, int& numOfSol )
{
    double f, g, h;
    double i, j, k, l, m, n, p, po;
    double r, s, t, u;
    double x1, x2, x3; 
  //  cout << "CUBIC EQUATION : " << a << " x^3 + " << b << " x^2 + " << c <<" x + " << d << " = 0" << endl;

    f = ((3*c/a)-((b*b)/(a*a)))/3;
    g = ((2*(b*b*b)/(a*a*a))-(9*b*c/(a*a))+(27*d/a))/27;   
    h = ((g*g)/4)+((f*f*f)/27);


    if(f==0 && g==0 && h==0){     // all roots are real and equal
        x1 = pow((d/a),0.33333333333333333333333333333333);
        x2 = pow((d/a),0.33333333333333333333333333333333);
        x3 = pow((d/a),0.33333333333333333333333333333333);

        // cout << "x = " << x1 << endl;
        // cout << "x = " << x2 << endl;
        // cout << "x = " << x3 << endl;

        _x1 = x1;
        _x2 = x2;
        _x3 = x3;
        numOfSol = 3;
    }
    else if(h<=0){         // all 3 roots are real
        i = pow((((g*g)/4)-h),0.5);
        j = pow(i,0.33333333333333333333333333333333);
        k = acos((g/(2*i))*-1);
        l = j * -1;
        m = cos(k/3);
        n = sqrt(3) * sin(k/3);
        p = (b/(3*a))*-1;

        x1 = (2*j)*m-(b/(3*a));
        x2 = l * (m+n) + p;
        x3 = l * (m-n) + p;
        // cout << "x = " << x1 << endl;
        // cout << "x = " << x2 << endl;
        // cout << "x = " << x3 << endl;

        _x1 = x1;
        _x2 = x2;
        _x3 = x3;
        numOfSol = 3;
    }
    else if(h>0){
        r = ((g/2)*-1)+pow(h,0.5);
        s = pow(r,0.33333333333333333333333333333333);
        t = ((g/2)*-1)-pow(h,0.5);
        u = pow((t),0.33333333333333333333333333333333);
        x1 = (s+u) - (b/(3*a));
        //cout << "x = " << x1 << endl;
        _x1 = x1;
        numOfSol = 1;
    }
    
}

typedef struct mbuf MBuf;

enum class msgType { CONNECT, DISCONNECT, MSG };
class ClientMassage
{
public:
    msgType type;
    int a,b,c,d;
    pid_t pid;
    ClientMassage(msgType _type)
    {
        type = _type;
    }
    ClientMassage(int _a, int _b, int _c, int _d, pid_t _pid)
    {
        a = _a;
        b = _b;
        c = _c;
        d = _d;
        type = msgType::MSG;
    }
};
class ServerMassage
{
public:
    int numOfSol;
    double x1,x2,x3;
    ServerMassage(int _numOfSol, int _x1 = 0, int _x2 = 0, int _x3 = 0)
    {
        numOfSol = _numOfSol;
        x1 = _x1;
        x2 = _x2;
        x3 = _x3;
    }
    void Print()
    {
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
        cout << "x3 = " << x3 << endl;
    }  
};

struct mbuf 
{
    long mtype;
    char mtext[MSG_MAX];
} mobj;

int main(int argc,char* argv[])
{
    strcpy (mobj.mtext, "Hello");
    mobj.mtype = 15;
    int pid = fork();
    int pid2 = 100;
    // if (pid > 0)
    // {
    //     pid2 = fork();
    // }
    int fd; 
    bool flag = true;
    srand(time(NULL));

    if (pid > 0 && pid2 > 0)
    {
        // Server
        fd = msgget(15,IPC_CREAT | 0666);   // открываем очередь
        if (fd == -1){ perror("create Q:"); exit(-1);}

        MBuf ServerBuf; // задаем буфер для сервера
        int clientCounter = 1;

        while (1){
            msgrcv(fd, &mobj, MSG_MAX , 0 ,  0); // получаем сообщение

            ClientMassage* clp = (ClientMassage*)(&mobj.mtext); //интерпретируем его 
            if (clp->type == msgType::CONNECT)
            {
               // clientCounter++;
            }
            else if (clp->type == msgType::DISCONNECT)
            {
                cout << "Client disconnected" << endl;
                clientCounter--;
                // cout << "clientCounter = "<<clientCounter << endl;
                if (clientCounter == 0){
                    break;
                }
                cout << endl;
            }
            else if (clp->type == msgType::MSG)
            {
                double x1,x2,x3;
                int num;
                cubic(clp->a,clp->b,clp->c,clp->d, x1,x2,x3, num);

                // if (num == 1)
                // {
                //     cout << "Cubic:" << endl;
                //     cout << "x = " << x1 << endl;
                // }
                // else
                // {
                //     cout << "Cubic:" << endl;
                //     cout << "x = " << x1 << endl;
                //     cout << "x = " << x2 << endl;
                //     cout << "x = " << x3 << endl;
                // }
                
                ServerMassage* SMsg = new ServerMassage(num,x1,x2,x3); //Отправляем ответ
                SMsg->x1 = x1;
                SMsg->x2 = x2;
                SMsg->x3 = x3;
                SMsg->numOfSol = num;
                memcpy(ServerBuf.mtext, SMsg, sizeof(*SMsg));
                ServerBuf.mtype = clp->pid;
                msgsnd(fd,&ServerBuf, sizeof(*SMsg) + 1, IPC_NOWAIT); 
            }
        }

        //Завершаем работу
        wait(NULL);
        int rc = msgctl(fd, IPC_RMID,0);
        if (rc == -1){ perror("masgctl");}
    }
    else
    {
        //Client    
        int a=1, b=-5, c=8, d=-4;


        fd = msgget(15,IPC_CREAT | 0666);
        if (fd == -1){ perror("create Q:"); exit(-1);}
        
        MBuf ClientBuf; // задаем буфер для клиента

        ClientMassage* CMsg = new ClientMassage(msgType::CONNECT); //Сообщение о подключении
        memcpy(mobj.mtext, CMsg, sizeof(CMsg));
        msgsnd(fd,&mobj, sizeof(*CMsg) + 1, IPC_NOWAIT); 


        CMsg = new ClientMassage(a,b,c,d, getpid()); //Сообщение с параметрами 
        CMsg->pid = getpid();
        //cout << "Getpid() = " <<CMsg->pid << endl;
        memcpy(mobj.mtext, CMsg, sizeof(*CMsg));        
        msgsnd(fd,&mobj, sizeof(*CMsg) + 1, IPC_NOWAIT); 

        msgrcv(fd, &ClientBuf, MSG_MAX , getpid(),  0); // получаем сообщение
        ServerMassage* SMsg = new ServerMassage(0); 
        SMsg = (ServerMassage*)(ClientBuf.mtext);
        cout << "Cubic equation:" << endl;
        cout << a << " * x^3 + " << b << " * x^2 + " << c << " * x + "<< d <<" = 0" << endl;
        cout << "Rezul: " << endl;
        SMsg->Print();

        CMsg = new ClientMassage(msgType::DISCONNECT); //Сообщение о отключении
        memcpy(mobj.mtext, CMsg, sizeof(CMsg));
        msgsnd(fd,&mobj, sizeof(*CMsg) + 1, IPC_NOWAIT);
    }
    return 0;
}
