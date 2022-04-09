#include "Sourse.h"
using namespace std;


bool parse(const string& str, string& name, string& message) 
{
    int i = 0;
    while (i < str.length() && str[i] != '|')
    {
        name += str[i];
        i++;
    }
    i++;

    while (i < str.length())
    {
        message += str[i];
        i++;
    }
    return !(message.length() == 0 || name.length() == 0);
}

int main(int argc, char *argv[]){

    if (argc != 7)
    {
        cout << "ERROR: argc mast be 7"<<endl;
        exit(-1);
    }
    if (string(argv[1]) != string("-u"))
    {
        cout << "ERROR: the first parameter should be the name"<<endl;
        exit(-1);
    }
    if (string(argv[3]) != string("-l"))
    {
        cout << "ERROR: the third parameter must be the host"<<endl;
        exit(-1);
    }
        if (string(argv[3]) != string("-l"))
    {
        cout << "ERROR: the fifth parameter must be the end point"<<endl;
        exit(-1);
    }

    pid_t pid = fork();
    if (pid > 0){

        //server
        int socket;
        struct sockaddr_in addr;
        socket = Socket(SOCK_DGRAM);

        struct in_addr ip;
        unsigned port;
        parse_ip_port(argv[4], &port, &ip);

        addr.sin_family = AF_INET;
        addr.sin_port = port;
        addr.sin_addr = ip;

        unsigned int len = sizeof(addr);

        Bind(socket, addr);

        char recvBuf[BUFSIZE];

        cout << "Server Started" << endl;

        while(1)
        {
            int n = recvfrom(socket,recvBuf, BUFSIZE, 0, (struct sockaddr *)&addr, &len);
            // int n = recvfrom(socket,recvBuf, BUFSIZE, 0, 0, 0);
            recvBuf[n] = 0;
            string name, msg;
            parse(recvBuf,name,msg);

            if (msg == string("quit!"))
            {
                //полсать сигнал клиенту
                
                if (kill(pid,SIGTERM) == -1)
                {
                    perror("kill: ");
                }
                exit(1);
            }

            cout << name << ":  " << msg << endl;
        }

        wait(NULL);
        return 0;
    }
    else
    {
        //client
        sleep(1);
        int socket;
        socket = Socket(SOCK_DGRAM);

        char buf[BUFSIZE];
        struct sockaddr_in addr;
        struct in_addr ip;
        unsigned port;
        parse_ip_port(argv[6], &port, &ip);

        addr.sin_family = AF_INET;
        addr.sin_port = port;
        addr.sin_addr = ip;

        cout << "Client Started" << endl;
        // cout << "input name"<<endl <<">>";
        // cin.getline(buf,100);
        string name = argv[2];



        bool exitFlag = false;
        strcpy(buf, (name + string("|") + "Conected").c_str());
        int n = sendto(socket, buf, sizeof(buf), 0 ,(struct sockaddr *)&addr, sizeof(addr));
        if (n != 0){ perror("sendto: ");}
        while(1)
        {
            cin.getline(buf,BUFSIZE);
            if (string(buf) == "quit!")
            {
                //TODO: отправить себе и др клиенту сообщение о закрытии чата.
                strcpy(buf, (name + string("|") + string(buf)).c_str());
                sendto(socket, buf, sizeof(buf), 0 ,(struct sockaddr *)&addr, sizeof(addr));

                struct in_addr ip2;
                unsigned port2;
                parse_ip_port(argv[4], &port2, &ip2);

                addr.sin_family = AF_INET;
                addr.sin_port = port2;
                addr.sin_addr = ip2;

                sendto(socket, buf, sizeof(buf), 0 ,(struct sockaddr *)&addr, sizeof(addr));
            }

            strcpy(buf, (name + string("|") + string(buf)).c_str());
            n = sendto(socket, buf, sizeof(buf), 0 ,(struct sockaddr *)&addr, sizeof(addr));
        }

        return 0;
    }
}