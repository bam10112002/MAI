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

        struct in_addr ip;
        unsigned port;
        parse_ip_port(argv[1], &port, &ip);

        addr.sin_family = AF_INET;
        addr.sin_port = port;
        addr.sin_addr = ip;

        // char* str = "127.0.0.1:5000";
        // parse_ip_port(str, &port, &ip);

        // addr.sin_family = AF_INET;
        // addr.sin_port = port;
        // addr.sin_addr = ip;

        // addr.sin_family = AF_INET;
	    // addr.sin_port = htons(port);
	    // addr.sin_addr.s_addr = htonl(INADDR_ANY);

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
        parse_ip_port(argv[2], &port, &ip);

        addr.sin_family = AF_INET;
        addr.sin_port = port;
        addr.sin_addr = ip;

        cout << "Client Started" << endl;
        cout << "input name"<<endl <<">>";
        cin.getline(buf,100);
        string name = buf;

        bool exitFlag = false;
        strcpy(buf, (name + string("|") + "Conected").c_str());
        int n = sendto(socket, buf, sizeof(buf), 0 ,(struct sockaddr *)&addr, sizeof(addr));
        if (n != 0){ perror("sendto: ");}
        while(1)
        {
            cin.getline(buf,BUFSIZE);
            strcpy(buf, (name + string("|") + string(buf)).c_str());
            int n = sendto(socket, buf, sizeof(buf), 0 ,(struct sockaddr *)&addr, sizeof(addr));
        }

        return 0;
    }
}