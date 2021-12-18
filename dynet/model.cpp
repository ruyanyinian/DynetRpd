#include "dynet/model.hpp"
#include "dynet/globals.hpp"

namespace dynet {

ParameterStorage::ParameterStorage(const Dim& d, float scale, const std::string& name, Device* dev)
    : name(name), dim(d), updated(true), nonzero_grad(false), owner(nullptr), device(dev) {
    DYNET_ARG_CHECK(default_device != nullptr, 
                    "Attempting to define parameters before initializing DyNet. Be sure to call dynet::initialize() before defining your model.");
    values.d = g.d = d;
    values.device = g.device = device;
    
    }
}