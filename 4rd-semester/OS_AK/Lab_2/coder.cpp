#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <filesystem>
#include "src/Hamming/include/hamming.h"
namespace fs = std::filesystem;


void coder  (std::string inputFileName, std::string outFileName, int blockSize);
void decoder(std::string inputFileName, std::string outFileName, int blockSize);
void testCheckError();
void demon(std::string dirName);
// void checkFile(std::string fileName);

int main(int argc, char* argv[])
{
    int bits;
    std::string inName, outName;
    if (argc != 7)
    {
        cout << "argc is not valid, obtained value = " << argc << endl;
        return -1;
    }
    for (int i = 1; i < 7; i += 2)
    {
        if (std::string(argv[i]) == "-n")
            bits = std::stoi(argv[i+1]);

        else if (std::string(argv[i]) == "-i")
            inName = std::string(argv[i+1]);

        else if (std::string(argv[i]) == "-o")
            outName = std::string(argv[i+1]);

        else 
            std::cerr << "undefind key: " << argv[i] <<  endl;  
    }

    coder(inName, outName, bits);

    return 0;
}


void testCheckError()
{
    std::vector<u8> vec = {'b', 'a'};
    Hamming hm(16);
    hm.setArr(vec);
    cout << "Base Hamming massive : ";
    hm.binaryPrint();
    hm.set(10,0);
    cout << "Broken massive       : ";
    hm.binaryPrint();
    hm.ChangeError();
    cout << "Changed massive      : ";
    hm.binaryPrint();
}

void coder(std::string inputFileName, std::string outFileName, int blockSize)
{
    std::ifstream input(inputFileName);
    std::ofstream out(outFileName);
    if (!input || !out)
    {
        cout << "ERROR open file in coder" << endl;
        return;
    }

    bool endFile = false;
    while (!endFile)
    {
        std::vector<u8> arr((blockSize/8)+1);
        Hamming hm(blockSize);
        for (int i = 0 ; i < blockSize/8; i++)
        {
            char ch;
            if(input.get(ch))
            {
                arr[i] = ch;
            }
            else
            {   if (i == 0)
                {
                    input.close();
                    out.close(); 
                    return;
                }
                for (int j = i; j < blockSize/8; j++)
                    arr[j] = 0;
                endFile = !endFile;
                break;
            }
        }
        hm.setArr(arr);
        out << hm;
    }
    input.close();
    out.close();
}
void decoder(std::string inputFileName, std::string outFileName, int blockSize)
{
    std::ifstream input(inputFileName);
    std::ofstream out(outFileName);
    if (!input || !out)
    {
        cout << "ERROR open file in decoder\n";
        return;
    }
    Hamming hm(blockSize);
    while (!input.eof())
    {
        input >> hm;
        int err = hm.ChangeError();
        
        if (err != -1)
            cout << "ERROR in " << err << "\t" << endl;
        std::vector<u8> vec;
        vec = hm.getArr();
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i])
                out << char(vec[i]);
            if (vec[i] && err != -1)
                cout << char(vec[i]);
        }
    }
    input.close();
    out.close();
}
void demon(std::string dirName)
{
    std::ifstream input;
    for (const auto& entry : fs::directory_iterator(dirName))
    {
        Hamming hm(16);
        input.open(entry.path());
        if (!input)
        {
            cout << "ERROR open file in demon\n";
            return;
        }
        while (!(input.eof()))
        {
            input >> hm;
            int err = hm.ChangeError();
            if (err != -1)
                cout << "Error in file" << entry.path() << "ERROR in " << err << "\t" << endl;
        }
        input.close();
    }
}
