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
    /*下面是计算有多少是0维度的*/
    inline unsigned int num_nonone_dims() const {
        int ret = 0;
        for (size_t i = 0; i < nd; i++) {
            if(d[i] != 1) {
                ++ret;
            }
        }
        return ret;
    }

    /**
     * 删除指定的维度i
    */
    inline unsigned int delete_dim(unsigned int i) {
        if(i == nd - 1) {
            if(nd == 1) {
                d[0] = 1;
            }
            else {
                --nd;
            }
        }
        else {
            for(; i + 1 < nd; ++i) {
                d[i] = d[i+1];
            }
            --nd;
        }
    }
    inline void delete_dims(const std::vector<unsigned int>& dims, bool reduce_batch){
        std::vector<bool> deleted_dims(nd, false);

        for(unsigned int i = 0; i < dims.size(); i++) {
            deleted_dims[dims[i]] = true;
        }

        if(dims.size() == nd) {
            nd = 1;
            d[0] = 1;
        } else {
        int flag = 0;
        for(unsigned int i = 0; i < nd; i++) {
            if(!deleted_dims[i])
            d[flag++] = d[i];
        }
        nd = flag;
        }

        if(reduce_batch)
        bd = 1;
    }
    unsigned int d[DYNET_MAX_TENSOR_DIM];
    unsigned int nd;
    unsigned int bd;
};

std::ostream& operator<<(std::ostream& os, const Dim& d);

}
#endif 