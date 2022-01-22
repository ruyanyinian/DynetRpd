#include "dynet/tensor.hpp"
#include "dynet/devices.hpp"

using namespace std;
int main() {
    float* data = new float[4]{0.,1.,2.,3};
    const dynet::Dim d({4}, 1); 
    dynet::DeviceMempoolSizes mp("128");
    dynet::Device_CPU dev(0, mp, false);
    dynet::Tensor t(d, data, &dev, dynet::DeviceMempool::NONE);
    std::cout << t << endl;
}