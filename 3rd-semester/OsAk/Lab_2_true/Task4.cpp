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

using namespace std;

int main()
{
    char* fileName = "Task1.cpp";
    char* newFileName = "TaskSim.cpp";

    symlink(fileName, newFileName);

    struct stat sb;
    if( stat(newFileName, &sb) != -1 ) 
    {
        
        std::cout << sb.st_dev      << "	ID of device containing file" << std::endl;
    	std::cout << sb.st_ino      << "	inode number" << std::endl;
   	    std::cout << sb.st_mode     << "	protection" << std::endl;
    	std::cout << sb.st_nlink    << "	number of hard links" << std::endl;
    	std::cout << sb.st_uid      << "	user ID of owner" << std::endl;
    	std::cout << sb.st_gid      << "	group ID of owner" << std::endl;
    	std::cout << sb.st_rdev     << "	device ID (if special file)" << std::endl;
    	std::cout << sb.st_size     << "	total size, in bytes" << std::endl;
    	std::cout << sb.st_blksize  << "	blocksize for file system I/O" << std::endl;
    	std::cout << sb.st_blocks   << "	number of 512B blocks allocated" << std::endl;
    	std::cout << sb.st_atime    << "	time of last access" << std::endl;
    	std::cout << sb.st_mtime    << "	time of last modification" << std::endl;
    	std::cout << sb.st_ctime    << "	time of last status change" << std::endl;
    

    }

    return 0; 
}