#ifndef DYNET_GLOBALS_HPP
#define DYNET_GLOBALS_HPP

#include <random>

namespace dynet {
class Device;
class NamedTimer;
extern std::mt19937* rndeng;
extern Device* default_device;
extern NamedTimer timer; // debug timing in executors.
}
#endif