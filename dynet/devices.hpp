#ifndef DYNET_DEVICE_HPP
#define DYNET_DEVICE_HPP
#include <unordered_map>
#include <vector>
#include <string>
#include <exception>
#include <unsupported/Eigen/CXX11/Tensor>

#include "dynet/device-structs.hpp"
#include "dynet/globals.hpp"
#include "dynet/mem.hpp"
#include "dynet/aligned-mem-pool.hpp"

namespace Eigen {
    struct DefaultDevice;
    class CudaStream;
    struct GpuDevice;
}

namespace dynet {
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
    // virtual DeviceMempoolSizes mark(ComputationGraph *cg);
    virtual void revert(const DeviceMempoolSizes & cp);
    void allocate_tensor(DeviceMempool mem_pool, Tensor & tensor);
    std::vector<AlignedMemoryPool*> pools;
};

class Device_CPU : public Device {
public:
    typedef Eigen::DefaultDevice EigenDeivce;
    explicit Device_CPU(int my_id, const DeviceMempoolSizes& mb, bool shared);
    ~Device_CPU();
    CPUAllocator cpu_mem;
    Eigen::DefaultDevice* edevice;
    MemAllocator* shmem;
};

class DeviceManager final {
public:
    DeviceManager();
    ~DeviceManager();
    void clear();
    void add(Device* d);
    Device* get(size_t i) { return devices[i]; }
    size_t num_devices() const { return devices.size(); }
    const std::vector<Device*>& get_devices() const { return devices; }
    Device* get_global_device(const std::string& name);
    
    // no copying allowed
    DeviceManager(const DeviceManager &) = delete;
    void operator=(const DeviceManager &) = delete;

private:
    std::vector<Device*> devices;
    std::unordered_map<std::string, Device*> devices_map;
};



} // namespace dynet

#endif /*dynet_devices_hpp*/