#ifndef DYNET_DEVICE_STRUCTS_HPP
#define DYNET_DEVICE_STRUCTS_HPP

namespace dynet {

enum class DeviceType {CPU, GPU};
enum class DeviceMempool {FXS = 0, DEDFS = 1, PS = 2, SCS = 3, NONE = 4};
struct Tensor; 

struct DeviceMempoolSizes {
    size_t used[4];
    
};

}
#endif /*DYNET_DEVICE_STRUCTS_HPP*/