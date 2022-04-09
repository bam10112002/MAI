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

        int socket;
        struct sockaddr_in addr;
        socket = Socket(SOCK_DGRAM);

        //server addr
        addr.sin_family = AF_INET;
        addr.sin_port = htons(5000); // port
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //id
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
        while(1)
        {
            string s;
            cin >> s;
            cout << "Me: " << s << endl;
        }
        return 0;
    }
}