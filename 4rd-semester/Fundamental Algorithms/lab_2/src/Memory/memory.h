#ifndef MEM_H
#define MEM_H

#include <stdlib.h>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "../Exeptions/exeptions.h"

#define MEMSIZE 128
#define DELTA 8

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i16 = int16_t;

// main allocator interface 
class MemAllocInterface
{
 public:
    virtual ~MemAllocInterface(){}
    virtual void print_data() = 0;
    virtual void* m_malloc(size_t size) = 0;
    virtual void m_free(void* ptr) = 0;
};


// sourse file for simple allocator
class MemBlock
{
public:
    MemBlock(void* _addres, u16 _size);
    void* addres;
    u16 size;
};
class SimpleAlloc : public MemAllocInterface
{
 private:
    void* memptr;
    std::list<MemBlock> reserved, available;

 public:
    SimpleAlloc();
    ~SimpleAlloc();
    
    //Test Funck
    void print_data() override; 

    // Logic
    void* m_malloc(size_t size) override;
    void m_free(void* ptr) override;
};


class BorderAlloc : public MemAllocInterface
{
 private:
    void* memptr;
    class Iterator
    {
     private:
        void* ptr;
     public:
        Iterator(void* _ptr);
        bool isReserved();
        i16 size();
        void* getPointer();

        Iterator operator++(int);
        Iterator operator--(int);
        bool operator==(const Iterator & right) const;
    };
    Iterator ItBegin();
    Iterator ItEnd();

 public:
    BorderAlloc();
    ~BorderAlloc();

    //Test Funck
    void print_data() override; 

    // Logic
    void* m_malloc(size_t size) override;
    void m_free(void* ptr) override;

};

// using PList = std::list<void*>;
class TwinAlloc : public MemAllocInterface
{
 private:
    void* memptr;
    std::vector<std::list<void*>> aviableList;
    std::vector<std::list<void*>> reservedList;

    void* mergeRec(void*& ptr, int& k);

 public:
    TwinAlloc();
    ~TwinAlloc();

    void print_data() override;
    void* m_malloc(size_t size) override;
    void m_free(void* ptr) override;
};

// main memory class
class Memory : public MemAllocInterface
{
protected:
    static Memory* memory;
    MemAllocInterface* allocator;
private:
    
public:
    // Singleton
    Memory(Memory &other) = delete;
    void operator=(const Memory &) = delete;
    static Memory *GetInstance();

    // Logic
    Memory();
    ~Memory();
    void* m_malloc(size_t size) override;
    void m_free(void* ptr) override;

    //Test Funck
    void print_data() override; 
};

#endif
