#include "dynet/mem.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>

#include <sys/shm.h>
#include <sys/mman.h>

#include <fcntl.h>
#if !_WINDOWS
#include <mm_malloc.h>
#endif
// #include "dynet/except.hpp"
#include "dynet/devices.hpp"

using namespace std;
namespace dynet {

MemAllocator::~MemAllocator() {}

void* CPUAllocator::malloc(size_t n) {
    void* ptr = _mm_malloc(n, align); // align = 32
    if (!ptr) {
        // show_pool_mem_info();
        // 所有开辟内存的操作在这里开辟
        cerr << "CPU memory allocation failed n=" << n << " align=" << align << endl;
        // throw dynet::out_of_memory("CPU memory allocation failed");
    }
    return ptr;
}

void CPUAllocator::zero(void* p, size_t n) {
    memset(p, 0, n);
}

void CPUAllocator::free(void* mem) {
    _mm_free(mem);
}


void* SharedAllocator::malloc(size_t n) {
    void* ptr = mmap(NULL, n, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
    if (ptr == MAP_FAILED) {
        show_pool_mem_info();
        cerr << "Shared memory allocation failed n=" << n << endl;
        throw dynet::out_of_memory("Shared memory allocation failed");
    }
    return ptr;

}

void SharedAllocator::free(void* mem) {
//  munmap(mem, n);
}

void SharedAllocator::zero(void* p, size_t n) {
    memset(p, 0, n);
}

}