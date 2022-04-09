#include "Sourse.h"
#include <stdio.h>


using namespace std;

void TestSem(MySem sem, MyShMem sh)
{
    void* buf;
    buf = sh.GetMem();

    //сервер ждет клиента
    sem.GetSem(MySem::Msg::SERVER_RCV_REQUEST);

    //сообщение получено
    cout << (char*)buf << endl;
    strcpy((char*)buf, "Library server conected.");

    //возвращаем ответ
    sem.GetSem(MySem::Msg::SERVER_SND_REPLY);
}
int main(){
    MySem sem;
    MyShMem sh;
    sem.SetSem(0,1);
    cout << "Server started" << endl;
    TestSem(sem,sh);

    void* buf;
    while(1)
    {
        FILE* fd;
        buf = sh.GetMem();
        //сервер ждет клиента
        sem.GetSem(MySem::Msg::SERVER_RCV_REQUEST);

        //сообщение получено
        cout << "Received a request for a book: " << (char*)buf << endl;

        //поиск книги и копирование данных в область разделяемой памяти
        fd = fopen((char*)buf, "r");
        if (fd == NULL){ cout <<"book not found;"<<endl; strcpy((char*)buf, "no"); }
        else {cout <<"book is found;"<<endl; strcpy((char*)buf, "yes"); }
        strcpy((char*)buf, "Unfortunately, this part of the software is temporarily not working"); 

        //возвращаем ответ
        sem.GetSem(MySem::Msg::SERVER_SND_REPLY);

        int n;

        do
        {
            sem.printSem();
            cout << "wait" << endl;
            sem.GetSem(MySem::Msg::SERVER_RCV_REQUEST);

            //сообщение получено
            cout << "Received a request for a book: " << (char*)buf << endl;
            n = fread(buf, sizeof(char), 1024, fd);
            ((char*)buf)[n] = 0;

            // cout << "n = " << n << endl;
            //возвращаем ответ
            sem.GetSem(MySem::Msg::SERVER_SND_REPLY);
        } while(n >= 1024);
        cout << "file close" << endl << endl;

        fclose(fd);
    }



    return 0;
}
