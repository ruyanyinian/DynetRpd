#ifndef DYNET_DEVICES_HPP
#define DYNET_DEVICES_HPP

#include <unordered_map>
#include <string>
#include <exception>

namespace dynet {
//基类
class Device {
protected:
    // Device(int i, )

    //QUESTION(QINYU):基类的成员函数都被protected保护起来, 为了只是能够让子类使用吗? 另外在device.cc里面只能找到几个对device的成员函数的部分定义
    //QUESTION(QINYU):在初始化声明中,可以直接使用初始化列表去初始化函数吗?而且还可以定义,因为有{}
    Device(int i, DeviceType t, MemAllocator* m) : device_id(i), type(t), mem(m), pools(4, nullptr) {} 
    Device(const Device&) = delete; //禁止隐式调用拷贝构造函数
    Device& operator=(const Device&) = delete; //禁止隐式调用赋值构造函数
    virtual ~Device();
public:
};

} /*namespace:dynet*/

#endif /*DYNET_DEVICES_HPP*/