#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <sys/dir.h>
#include <dirent.h>

typedef struct dirent Dirent;

using namespace std;

int main()
{
    DIR *dir = opendir("./testdir");
    Dirent* file;
    while ((file = readdir(dir)) != NULL)
    {
        std::cout << file->d_name<< std::endl;
    }

    return 0; 
}