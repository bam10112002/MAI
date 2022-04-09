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
        //client
        
    int socket2;
    socket2 = Socket(SOCK_DGRAM);

    char buf2[BUFSIZE];
    struct sockaddr_in addr2;
    struct in_addr ip2;
    unsigned port2;
    parse_ip_port(argv[2], &port2, &ip2);

    addr2.sin_family = AF_INET;
    addr2.sin_port = port2;
    addr2.sin_addr = ip2;


    int socket;
    struct sockaddr_in addr;
    socket = Socket(SOCK_DGRAM);

    struct in_addr ip;
    unsigned port;
    parse_ip_port(argv[1], &port, &ip);

    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr = ip;
    unsigned int len = sizeof(addr);
    Bind(socket, addr);
    char recvBuf[BUFSIZE];



    cout << "Client Started" << endl;
    cout << "input name"<<endl <<">>";
    cin.getline(buf2,100);
    string name2 = buf2;

    bool exitFlag = false;
    strcpy(buf2, (name2 + string("|") + "Conected").c_str());
    int n2 = sendto(socket2, buf2, sizeof(buf2), 0 ,(struct sockaddr *)&addr2, sizeof(addr2));
    if (n2 != 0){ perror("sendto: ");}

    while (1){
    
        cin.getline(buf2,BUFSIZE);
        if (string(buf2) == string("quit!")){exitFlag = true;}
        strcpy(buf2, (name2 + string("|") + string(buf2)).c_str());
        n2 = sendto(socket, buf2, sizeof(buf2), 0 ,(struct sockaddr *)&addr2, sizeof(addr2));
        if (exitFlag){return 0;}
        
        int n = recvfrom(socket,recvBuf, BUFSIZE, 0, (struct sockaddr *)&addr, &len);
        // int n = recvfrom(socket,recvBuf, BUFSIZE, 0, 0, 0);

        recvBuf[n] = 0;
        string name2, msg;
        parse(recvBuf,name2,msg);
        if (msg == string("quit!")){return 0;}
        cout << name2 << ":  " << msg << endl;
        
    }
}