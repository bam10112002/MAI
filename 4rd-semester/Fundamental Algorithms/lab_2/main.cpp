#include <iostream>
#include <string>
#include <list>
#include "src/Memory/memory.h"
// TODO: добавить парсер

using namespace std;

void memTest();
void memTestPair1();
void memTestPair2();


int main()  
{
    memTest();
    memTestPair1();
    memTestPair2();


    return 0;
}


void memTest()
{
    Memory* memPtr = Memory::GetInstance();
    
    void* ptr1 = memPtr->m_malloc(10);
    void* ptr2 = memPtr->m_malloc(10);
    void* ptr3 = memPtr->m_malloc(23);
    void* ptr4 = memPtr->m_malloc(2);


    memPtr->m_free(ptr1);
    memPtr->m_free(ptr3);
    memPtr->m_free(ptr2);
    memPtr->m_free(ptr4);

    memPtr->print_data();
}
void memTestPair1()
{
    Memory* memPtr = Memory::GetInstance();
    void* ptr1 = memPtr->m_malloc(33);
}
void memTestPair2()
{
    Memory* memPtr = Memory::GetInstance();
    memPtr->print_data();
}

