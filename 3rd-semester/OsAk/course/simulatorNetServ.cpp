#include "Sourse.h"
#include "Msg.h"

using namespace std;

void TestMsgQ(int md);
void TestSem(MySem& sem, MyShMem& sh);

//MsgQ
void SendValMsg(Msg& msg, int& md);
Msg GetValMsg(int& md);

// Socket
int ConfSock();
Msg RecvSockVal(int sock);
void SendSockVal(Msg& msg, int sock);
Type RecvType(int sock);



int main()
{   
    cout << "NET server is startup" << endl;

    //подключение серверов
    int md = msgget(15,IPC_CREAT | 0666); 
    if (md == -1){ perror("create MSG queue error: "); exit(-1);}
    TestMsgQ(md);

    MySem sem;
    MyShMem sh;
    TestSem(sem,sh);


    int sock;
    int listener = ConfSock();


    while(1)
    {
        // подключаем клиента
        sock = accept(listener, NULL, NULL); // по sock получаем и отправляем сообщения
        if(sock < 0){perror("accept"); exit(3); }
        cout << "accept" << endl;

        Type msgType = RecvType(sock);
        cout << "type is recived" << endl;
        if (msgType == Type::MSG)
        {
            cout << "MSG TYPE"<<endl;
            cout << "type is msg" << endl;
            Msg msg = RecvSockVal(sock);
            cout << "msg is recived" << endl;
            SendValMsg(msg, md);
            msg = GetValMsg(md);
            cout <<"converted data: " << msg.val.data << endl;

            SendSockVal(msg,sock);
        }
        else if (msgType == Type::SEM)
        {
            cout << "SEM TYPE"<<endl;
            char buf[1024];
            int bytes_read = recv(sock, buf, 1024, 0);
            if (bytes_read < 0){ perror("recv"); exit(-1);}
            if (bytes_read == 0){ cout << "zero massage" << endl; break;}
            buf[bytes_read] = '\0';
            cout << "Received the title of the book:" << buf << endl;

            void* semBuf;

            //Посылаем запрос
            sem.GetSem(MySem::Msg::CLIENT_GET_MEM);
           
            semBuf = sh.GetMem();
            strcpy((char*)semBuf, buf);
            cout << "Memory access is obtained" << endl;
            //отправляем запрос
            sem.GetSem(MySem::Msg::CLIENT_SND_REQUEST);
            cout << "The request for the book has been sent";

            // ждем ответ
            sem.GetSem(MySem::Msg::CLIENT_RCV_REPLY);
            cout << "The response to the request was received" << endl;

            //получили ответ
            cout << (char*)semBuf << endl;
            send(sock, semBuf, sizeof(semBuf), 0);

            sem.SetSem(0,1);


            int n;
            do
            {
                sem.GetSem(MySem::Msg::CLIENT_GET_MEM);
                semBuf = sh.GetMem();


                sem.GetSem(MySem::Msg::CLIENT_SND_REQUEST);
                sem.GetSem(MySem::Msg::CLIENT_RCV_REPLY);
                n = strlen((char*)semBuf);
                // cout << (char*)semBuf << endl;
                // cout <<"n = "<< n << endl;

                send(sock, semBuf, strlen((char*)semBuf), 0);
                cout << "sem set(0, 1)" << endl;
                sem.SetSem(0,1);

            }while (n >= 1024);
        }
        else
        {
            cout << "some qq"<<endl;
        }
        close(sock);
        cout << "socket is closed" << endl << endl;
    }


    // Финальное закрытие
    int rc = msgctl(md, IPC_RMID,0);
    if (rc == -1){ perror("masgctl RMID: ");}
    return 0;
}


void TestMsgQ(int md)
{
    // Тест очереди сообщений
    // md - дескриптор очереди сообщений

    MBuf mobj;
    strcpy(mobj.mtext, "NET server is connected.");
    mobj.mtype = 5;
    msgSend(md, &mobj); 
    msgRcv(md, &mobj, 10);
    cout << mobj.mtext << endl;
}
void TestSem(MySem& sem, MyShMem& sh)
{
    void* buf;

    //Посылаем запрос
    sem.GetSem(MySem::Msg::CLIENT_GET_MEM);

    buf = sh.GetMem();
    strcpy((char*)buf, "Net server is connected");

    //отправляем запрос
    sem.GetSem(MySem::Msg::CLIENT_SND_REQUEST);

    // ждем ответ
    sem.GetSem(MySem::Msg::CLIENT_RCV_REPLY);

    //получили ответ
    cout << (char*)buf << endl;
    sem.SetSem(0,1);
}


//SendValMsg
void SendValMsg(Msg& msg, int& md)
{
    MBuf* buf = new MBuf;
    memcpy(buf->mtext, &msg, sizeof(Msg));
    buf->mtype = 5;
    md = msgSend(md, buf); 
}

Msg GetValMsg(int& md)
{
    MBuf* buf = new MBuf;
    md = msgRcv(md, buf, 10);
    return *((Msg*)buf->mtext);
}

int ConfSock() //сокет для конекта
{
    int listener;
    struct sockaddr_in addr;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = (PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    listen(listener, 5);
    return listener;
}


Msg RecvSockVal(int sock)
{
    char buf[1024];
    cout << "server wait value"<<endl;
    int bytes_read = recv(sock, buf, 1024, 0);
    cout << "server recv value" << endl;
    if (bytes_read <= 0){ perror("recv socket: "); }
    return *((Msg*)buf);
}

void SendSockVal(Msg& msg, int sock)
{
    char buf[1024];
    memcpy(buf, &msg, sizeof(msg));
    send(sock, buf, sizeof(msg), 0);
}

Type RecvType(int sock)
{
    char buf[1024];
    int bytes_read = recv(sock, buf, 1024, 0);
    return *((Type*)buf);
}