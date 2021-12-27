#ifndef DIM_HPP
#define DIM_HPP

#include <initializer_list>
#include <type_traits>
#include <stdexcept>
#include <iosfwd>
#include <cstring>
#include <vector>

#include "dynet/except.hpp"

#define DYNET_MAX_TENSOR_DIM 7

namespace dynet {
struct Dim
{
    Dim() : nd(0), bd(1) {}
    Dim(std::initializer_list<unsigned int> x) : nd(0), bd(1) {
        for (auto v : x) d[nd++] = v;
    }
    Dim(std::initializer_list<unsigned int> x, unsigned int b) : nd(0), bd(b) {
        for (auto v : x) d[nd++] = v;
    }
    
    Dim(const std::vector<long> & x) : nd(0), bd(1) {
        for (auto v : x) d[nd++] = static_cast<unsigned int>(v);
    }
    Dim(const std::vector<long> & x, unsigned int b) : nd(0), bd(b) {
        for (auto v : x) d[nd++] = static_cast<unsigned int>(v);
    }
    /**
     * batch_size就是所有的维度相乘
     */
    inline unsigned int batch_size() const {
        unsigned int p = 1;
        for (unsigned int i = 0; i < nd; ++i) p *= d[i];
        return p;
    }
    /**
     * 一个Batch的尺寸
     */
    inline unsigned int size() const {
        return batch_size() * bd;
    }

    inline unsigned int sum_dims() const {
        unsigned int p = 0;
        for (unsigned int i = 0; i < nd; i++) p += d[i];
        return p;
    }
    // 在这里我们要返回一个Dim的对象
    inline Dim single_batch() const {
        Dim r = *this;
        r.bd = 1;
        return r; 
    }
    inline unsigned int operator[](unsigned int i) const { return i < nd? d[i] : 1; }
    inline unsigned int size(unsigned int i) const { return (*this)[i]; }
    inline unsigned int ndims() const { return nd; }
    inline unsigned int rows() const { return d[0]; }
    inline unsigned int cols() const { return nd > 1 ? d[1] : 1; }
    inline unsigned int batch_elems() const { return bd; }
    
    unsigned int d[DYNET_MAX_TENSOR_DIM];
    unsigned int nd;
    unsigned int bd;
};

}
#endif 