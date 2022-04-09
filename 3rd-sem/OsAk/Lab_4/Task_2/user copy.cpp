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

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if (pid > 0){
        //server
        int socket;
        struct sockaddr_in addr;
        socket = Socket(SOCK_DGRAM);

        //server addr
        string str = "127.0.0.1";
        struct in_addr ip;
        inet_pton(AF_INET, str.c_str(), &ip);

        addr.sin_family = AF_INET;
        addr.sin_port = htons(stoi(string(argv[1]))); // port
        // addr.sin_addr.s_addr = ip;//ip
        inet_pton(AF_INET, str.c_str(), &addr.sin_addr );
        
        unsigned int len = sizeof(addr);

        Bind(socket, addr);

        char recvBuf[BUFSIZE];

        // recvBuf = malloc(1024);

        cout << "Server Started" << endl;

        while(1)
        {
            int n = recvfrom(socket,recvBuf, BUFSIZE, 0, (struct sockaddr *)&addr, &len);
            recvBuf[n] = 0;
            string name, msg;
            parse(recvBuf,name,msg);
            cout << name << ":  " << msg << endl;
        }
        wait(NULL);
        return 0;
    }
    else
    {
        //client
        sleep(2);
        int socket;
        socket = Socket(SOCK_DGRAM);

        char buf[BUFSIZE];
        // strcpy(buf,"Hello world!");

        
        string str = "127.0.0.1";
        struct in_addr ip;
        inet_pton(AF_INET, str.c_str(), &ip);

        //server addr
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(stoi(string(argv[2]))); // port
        // addr.sin_addr.s_addr = ip; //ip
        inet_pton(AF_INET, str.c_str(), &addr.sin_addr );

        cout << "Client Started" << endl;
        cout << "input name"<<endl <<">>";
        cin.getline(buf,100);
        string name = buf;


        while(1)
        {
            cin.getline(buf,BUFSIZE);
            strcpy(buf, (name + string("|") + string(buf)).c_str());
            // cout << buf<<endl;
            int n = sendto(socket, buf, sizeof(buf), 0 ,(struct sockaddr *)&addr, sizeof(addr));
        }

        return 0;
    }
}