#include "Sourse.h"

double Calculate(double a, double b , char op)
{
    switch (op){
        case '+': 
            return (a + b);
        case '-': 
            return (a - b);
        case 'x': 
            return (a * b);
        case '/': 
            if (b == 0)
            {
                cout << "Division by zero";
                exit(-1);
            }
            return (a / b);
    }
}

int main()
{
    //Сервер
    MySem sem;
    MyShMem sh;
    sem.SetSem(0,1);
    void* buf;

    cout << "Server started" << endl;


    //Запускаем цикл сервера
    while(1)
    {
        Data* serverData = nullptr;
        buf = sh.GetMem();

        cout << "server wait" << endl;
        sem.GetSem(MySem::Msg::SERVER_RCV_REQUEST);
        serverData = (Data*)buf;

        if (serverData->type != Data::Type::EXPR)
        {
            //TODO: Получен не тот тип Data
            return 0;
        }
        else 
        {
            if (serverData->b == 0 &&  serverData->op == '/')
            {
                Data data(string("Division by zero"));
                memcpy(buf, &data, sizeof(data));
            }
            else
            {
                double rez = Calculate(serverData->a, serverData->b, serverData->op);
                Data clientData(rez);
                memcpy(buf, &clientData, sizeof(clientData));
            }
        }

        sem.GetSem(MySem::Msg::SERVER_SND_REPLY);
    }
    return 0;
}