#include "memory.h"

//! Memory ============================================================
Memory* Memory::memory = nullptr;
Memory *Memory::GetInstance()
{
    if(memory == nullptr){
        memory = new Memory();
    }
    return memory;
}
Memory::Memory() : MemAllocInterface()
{
    // this->allocator = new SimpleAlloc();
    allocator = new TwinAlloc();
}
Memory::~Memory()
{
    delete allocator;
}
void* Memory::m_malloc(size_t size)
{
    if (size <= 0)
        return nullptr;
    return allocator->m_malloc(size);
}
void Memory::m_free(void* ptr)
{
    allocator->m_free(ptr);
}
void Memory::print_data()
{
    allocator->print_data();
}



//! MemBlock ==========================================================
MemBlock::MemBlock(void* _addres, u16 _size)
{
    addres = _addres;
    size = _size;
}



//! SimpleAlloc ======================================================
// Test Funck
void SimpleAlloc::print_data()
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
SimpleAlloc::SimpleAlloc() : MemAllocInterface()
{
    if(!(memptr = (void*)malloc(MEMSIZE * sizeof(char))))
    {
        throw stdMallocExeption();
    }
    available.push_front(MemBlock(memptr, MEMSIZE));
}
SimpleAlloc::~SimpleAlloc()
{
    if (memptr)
        free(memptr);
}
void* SimpleAlloc::m_malloc(size_t size)
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
void SimpleAlloc::m_free(void* ptr)
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

//! BorderAlloc =====================================================
BorderAlloc::BorderAlloc() : MemAllocInterface()
{
    if(!(memptr = (void*)malloc(MEMSIZE * sizeof(char))))
    {
        throw stdMallocExeption();
    }

    *(static_cast<i16*>(memptr)) = (-1) * (MEMSIZE - 2 * static_cast<i16>(sizeof(i16)));
    *(reinterpret_cast<i16*>(static_cast<char*>(memptr) + MEMSIZE - sizeof(i16))) = (-1) * (MEMSIZE - 2 * static_cast<i16>(sizeof(i16)));
}
BorderAlloc::~BorderAlloc()
{
    if (memptr)
        free(memptr);
}
void BorderAlloc::print_data()
{
    auto it = ItBegin();
    while (!(it == ItEnd()))
    {
        if (it.isReserved())
            std::cout << "Reserved: ";
        else
            std::cout << "Avalable: ";

        std::cout << it.size() << std::endl;
        it++;
    }
}
void* BorderAlloc::m_malloc(size_t size)
{
    auto it = ItBegin();
    while (!(it == ItEnd()))
    {
        if (!(it.isReserved()) && it.size() >= static_cast<i16>(size))
        {
            if (it.size() -  static_cast<i16>(size) <= static_cast<int>(sizeof(i16) * 2))
                size = it.size();
            if (it.size() ==  static_cast<i16>(size))
            {
                void* ptr = it.getPointer();
                *(static_cast<char*>(ptr) + abs(*static_cast<i16*>(ptr))) *= -1;
                *static_cast<i16*>(ptr) *= -1;
                return NULL;
            }
            else 
            {
                i16 itSize = it.size();
                char* ptr = static_cast<char*>(it.getPointer());
                void* resPtr;

                // задаем первый блок
                *(reinterpret_cast<i16*>(ptr)) = (abs(itSize) - size - 2 * sizeof(i16)) * (-1);
                ptr += (abs(itSize) - size - 2 * sizeof(i16)) + sizeof(i16);
                *(reinterpret_cast<i16*>(ptr)) = (abs(itSize) - size - 2 * sizeof(i16)) * (-1);

                // задаем второй блок
                ptr += sizeof(i16);
                *(reinterpret_cast<i16*>(ptr)) = size;
                resPtr = ptr;
                ptr +=  sizeof(i16) + size;
                *(reinterpret_cast<i16*>(ptr)) = size;

                return resPtr;
            }
        }
        it++;
    }
    return NULL;
}
void BorderAlloc::m_free(void* ptr)
{
    auto it = ItBegin();
    while (!(it == ItEnd()))   
    {
        if (it.getPointer() == ptr)
        {
            *static_cast<i16*>(ptr) = -1 * it.size();
            *reinterpret_cast<i16*>(static_cast<char*>(ptr) + sizeof(i16)+ it.size()) = -1 * it.size();

            auto next = it++;
            it--;
            if (!(next == ItEnd()) && !(next.isReserved()))
            {
                *static_cast<i16*>(ptr) = (-1) * (next.size() + it.size() + 2 * sizeof(i16));
                *(static_cast<char*>(ptr) + it.size() + sizeof(i16)) = it.size() * (-1);
            }
            if (!(it == ItBegin()))
            {
                auto prev = it--;
                it++;
                if (!(prev.isReserved()))
                {
                    ptr = prev.getPointer();
                    *static_cast<i16*>(ptr) = (-1) * (it.size() + prev.size() + 2 * sizeof(i16));
                    *(static_cast<char*>(ptr) + prev.size() + sizeof(i16)) = prev.size() * (-1);
                }
            }
            break;
        }
        it++;
    }
    // TODO: ошибка
}

// Sourse
BorderAlloc::Iterator BorderAlloc::ItBegin()
{
    return Iterator(memptr);
}
BorderAlloc::Iterator BorderAlloc::ItEnd()
{
    return Iterator(static_cast<char*>(memptr) + MEMSIZE);
}

// Iterator
BorderAlloc::Iterator::Iterator(void* _ptr)
{
    ptr = _ptr;
}
bool BorderAlloc::Iterator::isReserved()
{
    return *(static_cast<i16*>(ptr)) > 0;
}
i16 BorderAlloc::Iterator::size()
{
    return abs(*(static_cast<i16*>(ptr)));
}
BorderAlloc::Iterator BorderAlloc::Iterator::operator++(int)
{
    ptr = static_cast<char*>(ptr) + abs(*(static_cast<i16*>(ptr))) + 2 * sizeof(i16);
    return *this;
}
BorderAlloc::Iterator BorderAlloc::Iterator::operator--(int)
{
    // ptr = static_cast<char*>(ptr) - abs(*(static_cast<i16*>(ptr)));
    ptr = static_cast<char*>(ptr) - sizeof(i16);
    // std::cout << *static_cast<i16*>(ptr) << std::endl;
    ptr = static_cast<char*>(ptr) - abs(*static_cast<i16*>(ptr)) - sizeof(i16);
    return *this;
}
bool BorderAlloc::Iterator::operator==(const BorderAlloc::Iterator & right) const
{
    return ptr == right.ptr;
}
void* BorderAlloc::Iterator::getPointer()
{
    return ptr;
}


//! TwinAlloc =====================================================
TwinAlloc::TwinAlloc() : MemAllocInterface(), aviableList(static_cast<int>(log2(MEMSIZE)) + 1), reservedList(static_cast<int>(log2(MEMSIZE)) + 1)
{
    memptr = (void*)malloc(MEMSIZE * sizeof(char));
    if(memptr == NULL)
    {
        std::cout << "Memptr = " << memptr << std::endl;
        throw stdMallocExeption();
    }
    aviableList[static_cast<int>(log2(MEMSIZE))].push_back(memptr);
}
TwinAlloc::~TwinAlloc()
{
    free(memptr);
}

void* TwinAlloc::mergeRec(void* ptr, int & k)
{
    void* twin = nullptr;
    if ((unsigned long int)(ptr) % static_cast<int>(pow(2,k+1)) == 0)
    {
        twin = static_cast<char*>(ptr) - static_cast<int>(pow(2,k));
    }
    else
    {
        twin = static_cast<char*>(ptr) + static_cast<int>(pow(2,k));
    }

    auto it = std::find(aviableList[k].begin(), aviableList[k].end(), twin);
    if (it != aviableList[k].end())
    {
        aviableList[k].erase(it);
        aviableList[k].erase(std::find(aviableList[k].begin(), aviableList[k].end(), ptr));
        k++;
        if (twin > ptr)
        {
            aviableList[k].push_front(ptr);
            ptr = mergeRec(ptr, k);
        }
        else
        {
            aviableList[k].push_front(twin);
            ptr = mergeRec(twin, k);
        }
    }
    return ptr;
}

void TwinAlloc::print_data()
{
    int i = 0;
    for (auto kList : aviableList)
    {
        if (!kList.empty())
        {
            for (auto obg : kList)
            {
                std::cout << "AVIABLE: pointer = " << obg << "; size = " << pow(2,i) << std::endl;
            }
        }
        i++;
    }
    std::cout << "=====================>>><<<<====================" << std::endl;
    i = 0;
    for (auto kList : reservedList)
    {
        if (!kList.empty())
        {
            for (auto obg : kList)
            {
                std::cout << "Resolved: pointer = " << obg << "; size = " << pow(2,i) << std::endl;
            }
        }
        i++;
    }
}
void* TwinAlloc::m_malloc(size_t size)
{
    int k = ceil(log2(size));
    int find_k = k;
    while (find_k <= log2(MEMSIZE) && aviableList[find_k].empty())
    {
        find_k++;
    }
    if (find_k > log2(MEMSIZE))
    {
        return nullptr;
    }

    while (find_k > k)
    {
        aviableList[find_k-1].push_back(aviableList[find_k].front());
        aviableList[find_k-1].push_back(static_cast<char*>(aviableList[find_k].front()) + static_cast<int>(pow(2,find_k-1)));
        aviableList[find_k].pop_front();
        find_k--;
    }
    void* ptr = aviableList[find_k].front();
    aviableList[find_k].pop_front();
    reservedList[k].push_back(ptr);
    return ptr;
}
void TwinAlloc::m_free(void* ptr)
{
    int k = 0;
    for (auto list : reservedList)
    {
        auto it = std::find(list.begin(), list.end(), ptr);
        if (it != list.end())
        {
            reservedList[k].erase(std::find(reservedList[k].begin(), reservedList[k].end(), ptr));
            aviableList[k].push_back(ptr);
            ptr = mergeRec(ptr, k);
        }
        
        k++;
    }
}
