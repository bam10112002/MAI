#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <sys/dir.h>
#include <dirent.h>
#include <algorithm>

#include <vector>

typedef struct dirent Dirent;

using namespace std;

int main()
{
    vector<char*> vec;
    DIR *dir = opendir("./testdir");
    Dirent* file;
    while ((file = readdir(dir)) != NULL)
    {
        if (file->d_type != 4)
        {
            vec.push_back(file->d_name);
        }
    }


    sort(vec.begin(), vec.end(), [](char* a, char* b) 
    {
        struct stat sb;
        struct stat sb2;
        stat(a, &sb);
        stat(b, &sb2);

        return sb.st_mtime > sb2.st_mtime; 
    });

    for (auto obj : vec)
    {
       // struct stat sb;
        cout << obj << endl;
        //stat(obj, &sb);
       // cout <<"  .. "<< sb.st_mtime << endl;
    }
    return 0; 
}