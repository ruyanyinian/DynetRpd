#ifndef DYNET_DEVICE_HPP
#define DYNET_DEVICE_HPP
#include <unordered_map>
#include <string>
#include <exception>

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
    float* kSCALAR_MINUSONE;
    float* kSCALAR_ONE;
    float* kSCALAR_ZERO;
    std::string name;
    virtual DeviceMempoolSizes mark(ComputationGraph *cg);
    virtual void revert(const DeviceMempoolSizes & cp);
    void allocate_tensor(DeviceMempool mem_pool, Tensor & tensor);
    std::vector<AlignedMemoryPool*> pools;
};
} // namespace dynet

#endif /*dynet_devices_hpp*/