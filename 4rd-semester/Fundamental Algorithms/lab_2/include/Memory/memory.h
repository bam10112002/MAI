#ifndef MEM_H
#define MEM_H

#include <stdlib.h>
#include <list>
#include <iostream>

#define MEMSIZE 100
#define DELTA 8
using u8 = u_int8_t;
using u16 = u_int16_t;
using u32 = u_int32_t;
using u64 = u_int64_t;


class MemBlock
{
public:
    void* addres;
    u16 size;
    MemBlock(void* _addres, u16 _size)
    {
        addres = _addres;
        size = _size;
    }

    //TODO: убрать
    void print()
    {
        std::cout << addres  << " : " << size << std::endl;
    }

};


class Memory
{
protected:
    static Memory* memory;

private:
    void* memptr;
    std::list<MemBlock> reserved, available;

public:
    // Singleton
    Memory(Memory &other) = delete;
    void operator=(const Memory &) = delete;
    static Memory *GetInstance();

    //Test Funck
    void print_data();

    // Logic
    Memory();
    ~Memory();
    void* m_malloc(size_t size);
    void m_free(void* ptr);
};

#endif
