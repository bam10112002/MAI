#include "Sourse.h"
#include "Msg.h"
#include "cmath"

using namespace std;

//Взаимодействие с NET сервером
void TestMsgQ(int md); // проверка работы серверов
Msg GetMsg(int& md);
void SendMsg(Msg& msg, int& md);

//переводы велечин
Value toSi(Value& val);
Value toNS(Value& val, NSType ns);


int main()
{   
    cout << "Data server is startup" << endl;
    //подключение серверов
    int md = msgget(15,IPC_CREAT | 0666);   // открываем очередь
    if (md == -1){ perror("create MSG queue error: "); exit(-1);}
    TestMsgQ(md);

    while(1)
    {
        Msg netMsg = GetMsg(md);
        Value rez;
        rez = toSi(netMsg.val);
        if (netMsg.targetNS != NSType::SI)
            rez = toNS(rez, netMsg.targetNS);
        netMsg.val = rez;
        SendMsg(netMsg, md);
    }
    

    return 0;
}















Msg GetMsg(int& md)
{
    MBuf* buf = new MBuf;
    md = msgRcv(md, buf, 5);
    return *((Msg*)buf->mtext);
}
void SendMsg(Msg& msg, int& md)
{
    MBuf* buf = new MBuf;
    memcpy(buf->mtext, &msg, sizeof(Msg));
    buf->mtype = 10;
    md = msgSend(md, buf); 
}

void TestMsgQ(int md)
{
    // Тест очереди сообщений
    // md - дескриптор очереди сообщений

    MBuf mobj;
    msgRcv(md, &mobj, 5); 
    cout << mobj.mtext << endl;
    strcpy (mobj.mtext, "Data server is connected.");
    mobj.mtype = 10;
    msgSend(md, &mobj); 
}

Value toSi(Value& val)
{
    Value rez;
    rez.ns = NSType::SI;
    if (val.vType == ValType::DISTANCE)
    {
        rez.vType = ValType::DISTANCE;
        if (val.ns == NSType::BRITISH)
        {
            rez.data = val.data * 0.3048;
            //1 фут = 0.3408 м
        }
        else if (val.ns == NSType::OLDRUSSIAN)
        {
            rez.data = val.data * 2.1336;
            //1 сажень = 2.1336 м
        }
        else
        {
            //TODO: ошибочка
        }
    }
    else if (val.vType == ValType::SQUARE)
    {
        rez.vType = ValType::SQUARE;
        if (val.ns == NSType::BRITISH)
        {
            rez.data = val.data * pow(0.3048,2);
            //1 фут = (0.3408)^2 м
        }
        else if (val.ns == NSType::OLDRUSSIAN)
        {
            rez.data = val.data * pow(2.1336,2);
            //1 сажень = 2.1336 м
        }
        else
        {
            //TODO: ошибочка
        }
    }
    else if (val.vType == ValType::WEIGHT)
    {
        rez.vType = ValType::WEIGHT;
        if (val.ns == NSType::BRITISH)
        {
            rez.data = val.data * 6.35029318;
            //1 стон = 6.35029318 кг
        }
        else if (val.ns == NSType::OLDRUSSIAN)
        {
            rez.data = val.data * 0.41;
            //1 фунт 0.41 
        }
        else
        {
            //TODO: ошибочка
        }
    }
    else
    {
        //TODO: ошибочка
    }
    return rez;
}


Value toNS(Value& val, NSType ns)
{
    Value rez;
    rez.ns = ns;

    if (val.vType == ValType::DISTANCE)
    {
        rez.vType = ValType::DISTANCE;
        if (ns == NSType::BRITISH)
        {
            rez.data = val.data * 1/0.3048;
            //1 фут = 0.3408 м
        }
        else if (ns == NSType::OLDRUSSIAN)
        {
            rez.data = val.data * 1/2.1336;
            //1 сажень = 2.1336 м
        }
        else
        {
            //TODO: ошибочка
        }
    }
    else if (val.vType == ValType::SQUARE)
    {
        rez.vType = ValType::SQUARE;
        if (ns == NSType::BRITISH)
        {
            rez.data = val.data * pow(1/0.3048,2);
            //1 фут = (0.3408)^2 м
        }
        else if (ns == NSType::OLDRUSSIAN)
        {
            rez.data = val.data * pow(1/2.1336,2);
            //1 сажень = 2.1336 м
        }
        else
        {
            //TODO: ошибочка
        }
    }
    else if (val.vType == ValType::WEIGHT)
    {
        rez.vType = ValType::WEIGHT;
        if (ns == NSType::BRITISH)
        {
            rez.data = val.data * 1/6.35029318;
            //1 стон = 6.35029318 кг
        }
        else if (ns == NSType::OLDRUSSIAN)
        {
            rez.data = val.data * 1/0.41;
            //1 фунт 0.41 
        }
        else
        {
            //TODO: ошибочка
        }
    }
    else
    {
        //TODO: ошибочка
    }


    return rez;
}