#include <iostream>
#include <string>

#include <list>

#include "include/Memory/memory.h"
// TODO: добавить парсер


int main()
{
    Memory* memPtr = Memory::GetInstance();
    void* ptr1 = memPtr->m_malloc(1);
    void* ptr2 = memPtr->m_malloc(10);
    void* ptr3 = memPtr->m_malloc(34);

    memPtr->m_free(ptr2);
    // memPtr->m_free(ptr1);
    // memPtr->m_free(ptr3);

    // memPtr->print_data();
    return 0;

}

