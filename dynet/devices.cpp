#include <iostream>
#include <string>
#include <unsupported/Eigen/CXX11/Tensor>

#include "dynet/devices.hpp"
#include "dynet/str-utils.hpp"



using namespace std;

namespace dynet {

DeviceMempoolSizes::DeviceMempoolSizes(size_t total_size) {
    DYNET_ARG_CHECK(total_size > 0, "Attempt to allocate memory of size 0 in DeviceMempoolSizes");
    if (total_size < 4) {
        used[0] = used[0] = used[2] = used[3] = 1; // 1代表使用过的
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
Device::~Device() {}

DeviceMempoolSizes::DeviceMempoolSizes(const std::string& descriptor) {
    vector<string> strs = str_split(descriptor, ',');
    if (strs.size() == 1) {
        size_t total_size = stoi(strs[0]);
        DYNET_ARG_CHECK(total_size > 0, "Attempt to allocate memory of size 0 in DeviceMempoolSizes");
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
        DYNET_INVALID_ARG("the format of --dynet-mem is invalid: " << descriptor);
    }
}

void Device::allocate_tensor(DeviceMempool mp, Tensor& tens) {
    DYNET_ASSERT(mp != DeviceMempool::NONE, "Attempt to allocate tensor for NONE DeviceMempool");
    DYNET_ASSERT(pools[(int)mp] != nullptr, "Attempt to allocate tensor for null DeviceMempool");
    tens.v = (float*)pools[(int)mp]
    DYNET_ASSERT(tens.v != nullptr, "Allocated tensor is zero");
}

} /*namespace dynet*/