#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int main(int argc, char* argv[])
{	
    //std::ofstream fout;
	
    if (argc != 3) { 
        std::cout << "Error arguments" << std::endl;
        return 1; 
    }
    std::ifstream fin;
    fin.open(argv[1]);

    std::string input;
    while (std::getline(fin, input))
    {
        pid_t pid = fork();
        if (pid == 0)
        {
        // std::cout <<"main: "<< argv[2] <<" || "<< input<<std::endl;
            char *cstr = new char[input.length() + 1];
            strcpy(cstr, input.c_str());

            execl("./program_2","./program_2", argv[2], cstr, NULL);
        }
        else 
        {

        }
    }
    fin.close();
   // fout.close();
}