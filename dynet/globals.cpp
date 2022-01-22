#include "dynet/globals.hpp"
#include "dynet/devices.hpp"
// #include "dynet/timing.hpp"

namespace dynet {
    std::mt19937* rndeng = nullptr;
    Device* default_device = nullptr;
    float default_weight_decay_lambda;
    int autobatch_flag; 
    int profiling_flag = 0;
    // NamedTimer timer;
}