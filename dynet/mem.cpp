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
    void* ptr = _mm_malloc()
}
}