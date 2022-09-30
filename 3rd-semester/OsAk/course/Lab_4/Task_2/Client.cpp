#include "Sourse.h"
using namespace std;


int main(int argc, char *argv[])
{
    int socket;
    socket = Socket(SOCK_DGRAM);

    char buf[BUFSIZE];
    // strcpy(buf,"Hello world!");


    //server addr
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000); // port
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //id


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