#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <sys/dir.h>
#include <dirent.h>

#include <sys/stat.h>
#include <fstream>

typedef struct dirent Dirent;

using namespace std;

string parseName(char* oldName)
{
    int counter = 0;
    std::string name = "" ,num = "", ext = "", newFilename = "";
    int flag = 1;

    while (oldName[counter] != '\0')
    {
        if (oldName[counter] == '.'){flag++; counter++; continue;}
        if (flag == 1)
        {
           name += oldName[counter];
        }
        else if (flag == 2)
        {
           num += oldName[counter];
        }
        else if (flag == 3)
        {
            ext += oldName[counter];
        }  
        else if (flag == 4)
        {
            name = num;
            num = ext;
            ext = "";
            flag = 3;
        }
        counter++;
    }
    if (flag == 2)
    {
        ext = num;
        num = "1";
        newFilename = name + "." + num + "." + ext;
        struct stat sb;
        while ( stat(newFilename.c_str(), &sb) != -1)
        {
           num = to_string(stoi(num) + 1);
           newFilename = name + "." + num + "." + ext;
        }
        
    }
    else
    {
        num = to_string(stoi(num) + 1);
        newFilename = name + "." + num + "." + ext;
        struct stat sb;
        while ( stat(newFilename.c_str(), &sb) != -1)
        {
           num = to_string(stoi(num) + 1);
           newFilename = name + "." + num + "." + ext;
        }
    }
    return newFilename;
}

int main()
{
    char* fileName = "Task1.2.cpp";
    struct stat sb;
    if( stat(fileName, &sb) != -1 ) 
    {
        //файл существет
        char* newFilename[100];
        string newFilenameStr = parseName(fileName);

        link(fileName, newFilenameStr.c_str());
    }
    else 
    {
        std::ofstream out;			// поток для записи
    	out.open(fileName);
    }

    return 0; 
}