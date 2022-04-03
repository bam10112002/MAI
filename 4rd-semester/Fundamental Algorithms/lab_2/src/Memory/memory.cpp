#include "memory.h"

// Singleton
Memory* Memory::memory = nullptr;
Memory *Memory::GetInstance()
{
    if(memory == nullptr){
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
MemBlock::MemBlock(void* _addres, u16 _size)
{
    addres = _addres;
    size = _size;
}

Memory::Memory()
{
    if(!(memptr = (void*)malloc(MEMSIZE * sizeof(char))))
    {
        throw stdMallocExeption();
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
            reserved.push_front(MemBlock((char*)(*block).addres + (*block).size, size));

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
    // Поиск блока
    auto it_res = reserved.begin();
    while((*it_res).addres != ptr)
    {
        if (it_res == reserved.end())
        {
            // TODO: свой класс ошибок
            // throw this->MemoryError("Hello");
            std::cout << "free( " << ptr <<" ): erorr" << std::endl <<"Aborted";
            exit(-1);
        }
        it_res++;
    }

    // Ищем место для освободивегося блока
    auto it_av = available.begin();
    while (it_av != available.end() && (*it_res).addres > (*it_av).addres)
    {
        it_av++;
    }

    // Переносим его из списка заняты в список со свободными
    available.emplace(it_av, MemBlock((*it_res).addres, (*it_res).size));
    reserved.erase(it_res);


    // обединяем области перед освобожденным блоком и за ним
    auto it = available.begin();
    while((*it).addres != ptr)
    {
        if (it == available.end())
        {
            // throw this->MemoryError("Hello");
            std::cout << "some error";
            exit(-1);
        }
        it++;
    }

    //MERGE
    // Right block
    auto next = ++it;
    --it;
    if (next != available.end() && (char*)(*it).addres + (*it).size == (char*)(*next).addres)
    {
        (*it).size += (*next).size;
        available.erase(next);
    }
    
    // Left block
    auto prev = --it;
    ++it;
    if ((char*)(*prev).addres + (*prev).size == (char*)(*it).addres)
    {
        (*prev).size += (*it).size;
        available.erase(it);
    }


}