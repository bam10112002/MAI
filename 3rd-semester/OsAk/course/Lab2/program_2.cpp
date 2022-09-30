#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

    // std::ofstream fout(argv[0], std::ios::app);
    FILE *wfile;
	wfile = fopen(argv[1], "a");

    int i = 0;
    std::string num1, num2;
    char op;
   // std::cout << argv[1] << argv[2];

    while (argv[2][i] != ' ')
    {
        num1 += argv[2][i];
        i++;
    } 

    i++;
    if (argv[2][i] == '+' || argv[2][i] == '-' || argv[2][i] == '*' || argv[2][i] == '/')
    {
        op = argv[2][i];
        i++;
    }
    else 
    {
        //TODO: Error
    }

    i++;
    while (argv[2][i] != ' ')
    {
        num2 += argv[2][i];
        i++;
    } 

  //  std::cout << num1 << "|" << num2 << "|" << op << std::endl;
    //Вычисления
    double rez;
    if (op == '+')
    {
        rez = std::stod(num1) + std::stod(num2);
    }
    else if (op == '-')
    {
        rez = std::stod(num1) - std::stod(num2);
    }
    else if (op == '*')
    {
        rez = std::stod(num1) * std::stod(num2);
    }
    else
    {
        rez = std::stod(num1) / std::stod(num2);
    }

    //std::cout << rez<<std::endl;

    // fout << rez << std::endl;
    fprintf(wfile, "%lf\n", rez);

    // fout.close();

    return 0;   
}