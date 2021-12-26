#include "dynet/aligned-mem-pool.hpp"
#include "dynet/devices.hpp"

#include <sstream>


namespace dynet {
void* InternalMemoryPool::allocate(size_t n) {
    std::size_t rounded_n = a->round_up_align(n);
    if (rounded_n + used > capacity) {
        return 0;
    }
    void* res = static_cast<char*>(mem) + used; // 指针运算, 返回一个没有被占用的地址
    used += rounded_n;
    return res;
}

void InternalMemoryPool::sys_alloc(size_t cap) {
    capacity = a->round_up_align(cap);
    mem = a->malloc(capacity);
    // if (mem == NULL) DYNET_RUNTIME_ERR(name << " failed to allocate " << capacity);
    used = 0;
}

AlignedMemoryPool::AlignedMemoryPool(const std::string& name, size_t initial_cap, MemAllocator* a, size_t expanding_unit)
    : name(name), cap(initial_cap), a(a), current(0), expanding_unit(expanding_unit) {
        // DYNET_ARG_CHECK(cap > 0, "Attempt to allocate memory of size 0 in AlignedMemoryPool");
        pools.push_back(new InternalMemoryPool(name, cap, a));
    }

AlignedMemoryPool::~AlignedMemoryPool() {
    for (auto p : pools) {delete p;}
}

void* AlignedMemoryPool::allocate(size_t n) {
    void* res = pools[current]->allocate(n);
    if (res == 0) {
         size_t new_pool_size = (n + expanding_unit - 1) / expanding_unit * expanding_unit;
         pools.push_back(new InternalMemoryPool(name, new_pool_size, a));
         cap = new_pool_size;
         current++;
         res = pools[current]->allocate(n);
    }

    if (res == nullptr) show_pool_mem_info();
    return res;
}

void AlignedMemoryPool::free() {
    if (current > 0) {
        for (auto p : pools) { delete p; }
        pools.clear();
        pools.push_back(new InternalMemoryPool(name, cap, a));
        current = 0;
    }
    pools[0]->free();
}

void AlignedMemoryPool::used() {
    if (current == 0) {
        return pool[0]->used;
    }
    size_t = 0;
    for (auto p : pools) { res += p->used; }
    return res;
}

void AlignedMemoryPool::set_use(size_t s) {
    if (s != pools.back()->used) {
        // DYNET_ARG_CHECK(pools.size() == 1, "Dynet does not support both dynamic increasing of memory pool size, and automatic batching or memory checkpointing. If you want to use automatic batching or checkpointing, please pre-allocate enough memory using the --dynet-mem command line option (details http://dynet.readthedocs.io/en/latest/commandline.html).");
        pools[0]->used = s;   
    }
}

size_t AlignedMemoryPool::get_cap() {
    return cap;
}

}