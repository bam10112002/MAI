#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "src/Memory/memory.h"

#include <math.h>
// TODO: добавить парсер

using namespace std;

void memTest();
void memTestPair1();
void memTestPair2();
void memTest2();


int main()  
{
    Memory* mem = Memory::GetInstance();
    void* ptr = mem->m_malloc(12);
    // mem->print_data();
    void* ptr2 = mem->m_malloc(12);
    // mem->print_data();
    
    if (ptr2 > ptr)
    {
        std::cout << "true";
        mem->m_free(ptr2);
    }
    mem->print_data();
    // memTest();
    // memTestPair1();
    // memTestPair2();

    return 0;
}

void memTest2()
{
    Memory* mem = Memory::GetInstance();
    auto ptr1 = mem->m_malloc(10);
    auto ptr2 = mem->m_malloc(2);
    auto ptr3 = mem->m_malloc(17);

    mem->m_free(ptr1);
    mem->print_data();
    std::cout << "====================================" << std::endl;
    mem->m_free(ptr2);
    mem->print_data();
    std::cout << "====================================" << std::endl;
    mem->m_free(ptr3);
    mem->print_data();
}
void memTest()
{
    Memory* memPtr = Memory::GetInstance();
    
    void* ptr1 = memPtr->m_malloc(10);
    void* ptr2 = memPtr->m_malloc(10);
    void* ptr3 = memPtr->m_malloc(23);
    void* ptr4 = memPtr->m_malloc(2);

    memPtr->print_data();

    memPtr->m_free(ptr1);
    memPtr->m_free(ptr3);
    memPtr->m_free(ptr2);
    memPtr->m_free(ptr4);

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

