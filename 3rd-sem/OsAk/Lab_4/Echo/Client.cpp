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

using namespace std;

char message[1025];
char buf[1024];

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    // while(1)
    // {
        cin.getline(message,100);

        send(sock, message, sizeof(message), 0);
        // if (string(message) == "quit!"){break;}
        // cout << "client send" << endl;
        recv(sock, buf, sizeof(buf), 0);
        // cout << "client resive" << endl;
        
        cout << "Number of words: " << (int)*buf << endl << endl;
    // }
    close(sock);
    return 0;
}