#include "Sourse.h"


void parse(string& str, string& num1, string& num2, char& op)
{
    num1 = num2 = "";
    int i = 0, len = str.length();
    while(i < len)
    {
        if (str[i] == ' ')
        {
            while(str[i] == ' '){i++;}
            break;
        }
        num1 += str[i];
        i++;
    }
    while(i < len)
    {
        if (str[i] == ' ')
        {
            while(str[i] == ' '){i++;}
            break;
        }
        num2 += str[i];
        i++;
    }
    op = str[i];
}


int main(int argc, char* argv[])
{
    // if (argc != 4)
    // {
    //     cout << "Fatal ERROR argc mast be four"<<endl;
    //     exit(-1);
    // }

    //Клиент
    MySem sem;
    MyShMem sh;
    void* buf;

    while(1){
        string num1,num2, str;
        char op;
        cout << "input in postfix"<<endl;
        getline(cin,str);
        // cin >> num1 >> num2 >> op;
        parse(str,num1,num2,op);
        if (num1 == ""){exit(0);}
        cout << stod(num1) <<" " << op << " " << stod(num2) << endl;
        Data clientData(stod(num1), stod(num2), op );

        //Посылаем запрос
        sem.GetSem(MySem::Msg::CLIENT_GET_MEM);

        buf = sh.GetMem();
        memcpy(buf, &clientData, sizeof(clientData));
        
        //отправляем ответ
        sem.GetSem(MySem::Msg::CLIENT_SND_REQUEST);

        // ждем ответ
        sem.GetSem(MySem::Msg::CLIENT_RCV_REPLY);

        //получили ответ
        Data* serverData = (Data*)buf;
        if (serverData->type == Data::Type::ERROR )
        {
            cout << serverData->error << endl;
            return -1;
        }
        cout << endl << stod(num1) << " " <<op << " "<< stod(num2) << "  = ";
        cout << serverData->GetRez() << endl;

        //открываем доступ другим клиентам
        // sem.GetSem(MySem::Msg::RESET);
        sem.SetSem(0,1);
    }
    return 0;
}