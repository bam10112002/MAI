#include "memory.h"

// Singleton
Memory* Memory::memory= nullptr;
Memory *Memory::GetInstance()
{
    if(memory==nullptr){
        memory = new Memory();
    }
    return memory;
}

// Test Funck
void Memory::print_data()
{
    std::cout << "Available: " << std::endl;
    for (auto obj : available)
    {
        std::cout << obj.addres << " : " << obj.size << std::endl;
    }

    std::cout << std::endl << "Reserved: " << std::endl;
    for (auto obj : reserved)
    {
        std::cout << obj.addres << " : " << obj.size << std::endl;
    }
}

// Logic
Memory::Memory()
{
    if(!(memptr = (void*)malloc(20 * sizeof(char))))
    {
        std::cout << "mallock error: " << memptr << std::endl;
        exit(-1);
        //TODO: свой класс ошибок
    }
    available.push_front(MemBlock(memptr, MEMSIZE));
}
Memory::~Memory()
{
    if (memptr)
        free(memptr);
}

void* Memory::m_malloc(size_t size)
{
    for (auto block = available.begin(); block != available.end(); block++)
    {
        if ((*block).size > size)
        {   
            // Растяжка блока если остается маленький кусок
            if (size + DELTA >= (*block).size)
                size = (*block).size;

            (*block).size -= size;

            // Добавление блока в список занятых
            reserved.push_front(MemBlock((char*)(*block).addres + (*block).size - size, size));

            // Отчистка уже занятого блока
            if (!(*block).size)
                available.erase(block);

            return ((char*)(*block).addres + (*block).size);
        }

    }
    return nullptr;
}

void Memory::m_free(void* ptr)
{
    // поиск блока
    auto it_res = reserved.begin();
    while((*it_res).addres != ptr)
    {
        if (it_res == reserved.end())
        {
            std::cout << "some error";
            exit(-1);
        }
        it_res++;
    }

    // добавляем в свободный список
    if (available.empty())
    {
        available.push_front(MemBlock((*it_res).addres, (*it_res).size));
    } 
    else 
    {
        auto it_av = available.begin();
        while ((*it_av).addres > (*it_res).addres)
            it_av++;

        available.emplace(it_av, MemBlock((*it_res).addres, (*it_res).size));

        // if (it_av != available.begin())
        // {
        //     auto prev = --it_av;
        //     ++it_av;
        //     std::cout << (char*)(*it_av).addres - (char*)(*prev).addres << " | " <<  (*prev).size << std::endl;
        // }
    }


    reserved.erase(it_res);
}