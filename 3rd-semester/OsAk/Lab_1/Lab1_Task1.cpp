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
using namespace std;

bool exitRandom()
{
    int randomNum = rand()%100;
    return(randomNum <= 15);
    cout << "exit";
}

int GenerateRandom()
{
    int randomNum = rand()%100;
    if (randomNum <= 15)
    {
        return(3);
    }
    else if (randomNum <= 50)
    {
        return(2);
    }
     else if (randomNum <= 70)
    {
        return(1); 
    }
    else 
    {
        return(0);
    }

}

void RecursiveFork(int counter, bool mainFlag, char* FName)
{
    if (!exitRandom())
    {
        int gen = GenerateRandom();
       // cout << gen;
        for (int i = 0; i < gen; i++)
        {  
            int forkrez = fork();
            if (forkrez == 0)
            {
                RecursiveFork(counter + 1, 0, FName);
                break;
            }
            else if (forkrez > 0)
            {
                wait(nullptr);
            }
        }
    }

    // for (int i = 0; i < counter; i++)
    // {
    //     std::cout << "*";
    // }
    // std::cout << std::endl;
    
    ofstream of(FName, std::ios::app);
    of << counter + '0';
    of.close();

    if (!mainFlag)
    {
        cout << ".";
        _exit(0);
    }
}

int main()
{
    std::srand(time(0));
    
    char* name = "tmp.txt";

    RecursiveFork(1, true, name);


    ifstream iff("tmp.txt");
    string parse;
    std::map<int,int> _map;

    char ch;
    while((ch = iff.get()) != EOF)
    {
        _map[ch-'0' + 1] += 1;
        // if (_map.find(ch) == _map.end())
        // {
        //     _map[ch - '0'] = 1;
        // }
        // else
        // {
        //     _map[ch - '0'] +=1;
        // }
    }

    for (auto obj : _map)
    {
        cout <<obj.first << "  ";
        for(int i = 0; i <  obj.second;i++)
        {
            cout << "*";
        }
        cout << endl;

        // cout << obj.first << " - " << obj.second << endl;
    }


    return 0;
}