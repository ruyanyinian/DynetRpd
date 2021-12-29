#include "dynet/tensor.h"
#include "dynet/tensor-eigen.h"
#include "dynet/index-tensor.h"
#include "dynet/globals.h"
#include "dynet/except.h"
#include "dynet/devices.h"

#include <random>
#include <vector>
#include <cstring>
#include <algorithm>

namespace dynet {
bool Tensor::is_valid const {
    if (device->type == DeviceType::CPU) {
        const size_t s = d.size(); // 假设Dim d({224,224,3}, 32)其中32是batchsize, 然后d.size()是224*224*3*32
        //遍历tensor的每个元素
        for (unsigned int i = 0; i < s; ++i) {
            //NOTE: 这里的v是一个float类型的指针, 指向一个很长的数组, 数组的元素都是float类型的, 然后我们的v[num]就是对这一个数组进行取值。
            if (std::isnan(v[i]) || std::isinf(v[i]) {
                return false
            })
        }
        return true
    }
    return false
}


std::ostream& operator<<(std::ostream& os, const Tensor& t) {
    if (t.device->type == DeviceType::CPU) {
        os << mat(t);
    }
    return os;
}

real as_scalar(const Tensor& t) {
    if (t.d.size() != 1)
        throw std::runtime_error("Input tensor has more than one element, cannot convert to scalar.");
    real res = 0.;
    if (t.device->type == DeviceType::CPU) {
        return t.v[0];
    }
    return res        
}

vector<real> as_vector(const Tensor& v) {
    vector<real> res(v.d.size());
    if (v.device->type == DeviceType::CPU) {
        memcpy(&res[0], v.v, sizeof(real) * res.size());
    } else { throw std::runtime_error("Bad device type"); }
    return res;
}


}

