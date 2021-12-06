#ifndef DYNET_DEVICE_HPP
#define DYNET_DEVICE_HPP
#include "dynet/device-structs.hpp"
#include "dynet/globals.hpp"
#include "dynet/mem.hpp"

namespace dynet
{
class Device {
protected:
    Device(int i, DeviceType t, MemAllocator* m) : device_id(i), type(t), mem(m), pools(4, nullptr) {}
    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;
    virtual ~Device();

public:
    void reset_rng(unsigned int seed);
    int device_id;
    DeviceType type;
    MemAllocator* mem;
    
};
} // namespace dynet

#endif /*dynet_devices_hpp*/