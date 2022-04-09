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
#include <string>

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <map>
#include <fstream>

#define BUFSIZE 1024

using namespace std;

int parse_ip_port(const char *str, unsigned *port, struct in_addr *ip)
{
    // ip:port
    std::string string(str);
    std::string s_port;
    auto sep = string.find(':');
    if (sep == std::string::npos)
        return -1;
    s_port = string.substr(sep + 1);
    string = string.substr(0, sep);
    *port = std::stoul(s_port);
    if (inet_pton(AF_INET, string.c_str(), ip) < 0)
        return -1;
    return 0;
}

int Socket( int type, int domain = AF_INET, int protocol = 0)
{
    int sock = socket(domain, type, protocol);
    if (sock == -1)
    {
        std::cout << "ERROR in Socket" << std::endl;
        perror("socket: ");
    }
    return sock;
}

void Bind(int sid, struct sockaddr_in addr)
{
    unsigned int len = sizeof(addr);
    if(bind(sid, (struct sockaddr *)&addr, len) < 0)
    {
        perror("bind");
        exit(2);
    }
}

struct Data
{
    string name;
    string body;
    Data(string _name)
    {
        name = _name;
    }
};