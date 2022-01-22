#include <iostream>
#include <string>
#include <unsupported/Eigen/CXX11/Tensor>
#include "dynet/devices.hpp"
#include "dynet/str-utils.hpp"



using namespace std;

namespace dynet {

DeviceMempoolSizes::DeviceMempoolSizes(size_t total_size) {
    if (total_size < 4) {
        used[0] = used[1] = used[2] = used[3] = 1; 
    } else {
        used[0] = total_size / 4;
        used[1] = total_size / 4;
        used[2] = total_size / 4;
        used[3] = total_size / 4;
    }
}

/*
 * FXS   -> forward pass memory
 * DEDFS -> backward pass memory
 * PS    -> parameter memory
 * SCS   -> scratch memory (for use in temporary calculations)
 * NONE  -> when a memory pool has not been assigned yet
 */
DeviceMempoolSizes::DeviceMempoolSizes(size_t fx_s, size_t dEdfs_s, size_t ps_s, size_t sc_s) {
    used[0] = fx_s;
    used[1] = dEdfs_s;
    used[2] = ps_s;
    used[3] = sc_s;
}

DeviceMempoolSizes::DeviceMempoolSizes(const std::string& descriptor) {
    // 用法假设是 "24,36,32,40"
    vector<string> strs = str_split(descriptor, ','); // {24, 36, 32, 40}
    if (strs.size() == 1) {
        size_t total_size = stoi(strs[0]);
        if (total_size < 4) {
            used[0] = used[1] = used[2] = used[3] = 1;
        } else {
            used[0] = total_size / 4;
            used[1] = total_size / 4;
            used[2] = total_size / 4;
            used[3] = total_size / 4;            
        }
    } else if (strs.size() == 4) {
        used[0] = stoi(strs[0]);
        used[1] = stoi(strs[1]);
        used[2] = stoi(strs[2]);
        used[3] = stoi(strs[3]);  
    } else {
    }
}

Device::~Device() {}

// DeviceMempoolSizes Device::Mark(ComputationGraph* cg) {   // 计算图相关, 现在还没有彻底研究这段代码
//     cg->incremental_forward({cg, (VariableIndex)(cg->nodes.size() - 1)}); // needed so that we actually allocate the needed memory
//     return DeviceMempoolSizes(pools[0]->used(), pools[1]->used(), pools[2]->used(), pools[3]->used());
// }

void Device::revert(const DeviceMempoolSizes& cp) {

}

void Device::allocate_tensor(DeviceMempool mp, Tensor & tens) {

    tens.v = (float*)pools[(int)mp]->allocate(tens.d.size() * sizeof(float));
    tens.mem_pool = mp;
}

Device_CPU::Device_CPU(int my_id, const DeviceMempoolSizes& mbs, bool shared) : 
    Device(my_id, DeviceType::CPU, &cpu_mem), shmem(mem) {
    if (shared) shmem = new SharedAllocator();
    kSCALAR_MINUSONE = (float*)mem->malloc(sizeof(float) * 1);
    *kSCALAR_MINUSONE = -1.;
    kSCALAR_ONE = (float*)mem->malloc(sizeof(float) * 1);
    *kSCALAR_ONE = 1.;
    kSCALAR_ZERO = (float*)mem->malloc(sizeof(float) * 1);
    *kSCALAR_ZERO = 0.;
    name = "CPU";
    
    edevice = new Eigen::DefaultDevice;
    pools[0] = new AlignedMemoryPool("CPU forward memory", (mbs.used[0] << 20), &cpu_mem);
    pools[1] = new AlignedMemoryPool("CPU backward memory", (mbs.used[1] << 20), &cpu_mem);
    pools[2] = new AlignedMemoryPool("CPU parameter memory", (mbs.used[2] << 20), shmem);
    pools[3] = new AlignedMemoryPool("CPU scratch memory", (mbs.used[3] << 20), &cpu_mem);
    
}
Device_CPU::~Device_CPU() {}

DeviceManager::DeviceManager() {}
DeviceManager::~DeviceManager() {
    clear();
}

void DeviceManager::clear() {
  devices.clear();
}


void DeviceManager::add(Device* d) {
    devices.push_back(d);
    devices_map[d->name] = d;
}

Device* DeviceManager::get_global_device(const std::string& name) {
    if (name == "") {
        if (!dynet::default_device) {
        throw std::runtime_error("Default device does not exist"); // 如果default device没有赋值的话, 会抛出异常
        }
        return dynet::default_device;
    }
    auto it = devices_map.find(name);
    if (it == devices_map.end()) {
        throw std::runtime_error("Invalid device name: " + name);
    }
    return it->second;
}

DeviceManager* get_device_manager() {
    static auto device_manager = new DeviceManager();
    return device_manager;
}

} /*namespace dynet*/