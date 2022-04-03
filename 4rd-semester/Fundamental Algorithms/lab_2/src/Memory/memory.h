#ifndef MEM_H
#define MEM_H

#include <stdlib.h>
#include <list>
#include <iostream>
#include "../Exeptions/exeptions.h"

#define MEMSIZE 100
#define DELTA 8
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class MemAlocInterface
{
 public:
    virtual void print_data() = 0;
    virtual void* m_malloc(size_t size) = 0;
    virtual void m_free(void* ptr) = 0;
}

class MemBlock
{
public:
    MemBlock(void* _addres, u16 _size);
    void* addres;
    u16 size;
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
    class MemoryError;
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
