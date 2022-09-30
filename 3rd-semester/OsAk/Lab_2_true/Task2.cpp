#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <sys/dir.h>
#include <dirent.h>
#include <string.h>
#include <string>

typedef struct dirent Dirent;

using namespace std;

int main()
{
    DIR *dir = opendir("./testdir");
    Dirent* file;
    while ((file = readdir(dir)) != NULL)
    {
        struct stat sb;
        char* name;
        if (file->d_type != 4)
        {
            std::cout << file->d_name<< std::endl;
        }

        // string str = "./testdir/";
        // str += string(file->d_name);
        // cout << str.c_str() << endl;
      
        // if (stat( str.c_str(), &sb) != -1){
        //    // cout << sb.st_mode & S_IFMT << "||" <<  S_IFDIR << endl;
        //     if (sb.st_mode & S_IFMT == S_IFDIR)
        //     {
        //      std::cout << file->d_name<< std::endl;
        //     }
        // }
        // else 
        // {
        //     cout << "Error in: " << file->d_name << endl;
        // }
    }

    return 0; 
}