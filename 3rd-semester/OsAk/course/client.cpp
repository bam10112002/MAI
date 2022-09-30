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

#include "Sourse.h"

using namespace std;

Value inputVal()
{
    Value val;
    int tmp;
    cout << "Input number system" << endl;
    cout << "1 - Old Russian" << endl;
    cout << "2 - British" << endl;
    cout << "3 - Systeme international d'unites " << endl;
    cout << ">>";
    cin >> tmp;
    switch(tmp)
    {
        case 1:
            val.ns = NSType::OLDRUSSIAN;
            break;
        case 2:
            val.ns = NSType::BRITISH;
            break;
        case 3:
            val.ns = NSType::SI;
            break;
        default:
            cout << "ERROR" << endl;
            //TODO: ERROR;
    }
    
    cout << "Input value type" << endl;
    cout << "1 - Distanse" << endl;
    cout << "2 - Weight" << endl;
    cout << "3 - Square" << endl;
    cout << ">>";
    cin >> tmp;
    switch(tmp)
    {
        case 1:
            val.vType = ValType::DISTANCE;
            break;
        case 2:
            val.vType = ValType::WEIGHT;
            break;
        case 3:
             val.vType = ValType::SQUARE;
            break;
        default:
            cout << "ERROR" << endl;
            //TODO: ERROR;
    }

    double data;
    cout << "Input data to convert" << endl << ">>";
    cin >> val.data;
    cout << endl;
    return val;
}
NSType inputTargetNS()
{
    int tmp;
    cout << "Input number system" << endl;
    cout << "1 - Old Russian" << endl;
    cout << "2 - British" << endl;
    cout << "3 - Systeme international d'unites " << endl;
    cout << ">>";
    cin >> tmp;
    switch(tmp)
    {
        case 1:
            return NSType::OLDRUSSIAN;
        case 2:
            return NSType::BRITISH;
        case 3:
            return NSType::SI;
        default:
            cout << "ERROR" << endl;
    }
    return NSType::NONE;
}
bool exit()
{
    char tmp;
    while (1){
        cout << "Do you wish to continue [y/n]"<<endl;
        cout << ">>";
        cin >> tmp;
        switch(tmp)
        {
            case 'y':
                return false;
            case 'n':
                return true;
            default:
                cout << "please enter y/n" << endl << endl;
        }
    }
    
}
Type inputType()
{
    int tmp;
    while(1)
    {
        cout << "Input type"<<endl;
        cout << "1 - conversion of values" << endl;
        cout << "2 - Library" << endl;
        cout << ">>";
        cin >> tmp;
        switch(tmp)
        {
            case 1:
                return Type::MSG;
            case 2:
                return Type::SEM;
            default:
                cout << "Please choose one of the suggested options" << endl;
        }
    }
}

int main()
{

    Type tp;

    int sock;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    while(1) 
    {
        tp = inputType();
        if (tp == Type::MSG)
        {
            char buf[1024];

            Msg msg;
            msg.val = inputVal();
            msg.targetNS = inputTargetNS();

            //соединяем 
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("connect"); exit(2); }
        
            //отправляем тип
            memcpy(buf, &tp, sizeof(Type));
            send(sock, buf, sizeof(Type), 0);
            cout << "Type is sended" << endl;

            //отправляем данные
            memcpy(buf, &msg,sizeof(msg));
            send(sock, buf, sizeof(msg), 0);
            cout << "Msg is sended" << endl;

            int bytes_read = recv(sock, buf, 1024, 0);
            msg = *((Msg*)buf);
            cout << "Converted data: " << msg.val.data <<endl;
        }
        else
        {
            char buf[1024];
            char buf2[1024];

            cout << "The library has not been implemented yet" << endl;
            cout << "Enter the desired book title" << endl;
            cout << ">>";
            cin >> buf2;
            cout << "The book is being searched for: "<< buf2 << endl;

            sock = socket(AF_INET, SOCK_STREAM, 0);
            if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("connect"); exit(2); }

            //отправляем тип
            memcpy(buf, &tp, sizeof(Type));
            send(sock, buf, sizeof(Type), 0);
            cout << "Type is sended" << endl;
            if (tp == Type::SEM) { cout << "type is sem"<<endl;}

            send(sock, buf2, strlen(buf2), 0);
            int bytes_read = recv(sock, buf, 1024, 0);
            if (string((char*)buf) == "no")
            {
                cout << "The book was not found" << endl;
                close(sock);
                if (exit()) { break;}
                continue;
            }

            strcat(buf2, "_");
            FILE* fd;
            cout << "file is created" << endl;
            fd = fopen(buf2, "w");
            if (fd == NULL) { perror("Open file error: ");}


            do{
                cout << "wait recv" << endl;
                int bytes_read = recv(sock, buf, 1024, 0);
                // cout << (char*)buf;
                // ((char*)buf)[bytes_read] = 0;
                // cout << "bytes_read = " << bytes_read << endl; 
                
                fprintf(fd, "%s", (char*)buf);

            } while(bytes_read >= 1024);

            cout << endl;
            cout << endl;
            fclose(fd);
            // cout << "The remaining functions have not yet been implemented" << endl;

        }

        close(sock);
        if (exit()) { break;}
        cout << endl << endl;
    }
    return 0;
}