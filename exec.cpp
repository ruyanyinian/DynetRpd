#include "dynet/tensor.hpp"
using namespace std;
int main() {
    float* data = new float[4]{0.,1.,2.,3};
    const dynet::Dim d({4}, 1); 
    // FIXME: 目前需要把device_cpu做成库, 但是dim是不需要的是因为所有的实现是写在头文件里面的。
    dynet::Device_CPU* device = new dynet::Device_CPU(0, std::string("512"), false);
    dynet::Tensor t(d, data, device, dynet::DeviceMempool::FXS);
}