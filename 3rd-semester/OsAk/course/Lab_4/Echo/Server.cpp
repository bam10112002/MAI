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


int numOfWords(char* str)
{
    int num = 0;
    int i = 0;
    while(str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            while(i < str[i] != '\0' && str[i] == ' '){}
            num++;
        }
        i++;
    }
    if (num){num++;}
    return num;
}

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        cout << "Client conected" << endl;
        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            // cout << "{" << bytes_read << "}" << endl;
            // cout << "server resive" << endl;
            if(bytes_read <= 0)
            {
                // cout <<"bytes_read = " << bytes_read<<endl;
                break;
            }

            int n = 1;
            // cout << buf;
            for(int i = 0; i < bytes_read; i++)
            {
                if (buf[i] == ' ')
                {
                    n++;
                }
            }
            // cout << n << endl;

            *buf = (char)n;
            send(sock, buf, sizeof(int), 0);
            // cout << "Request processed" << endl;
        }
    
        close(sock);    
    }
    
    return 0;
}