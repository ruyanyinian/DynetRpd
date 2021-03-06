#ifndef DYNET_TENSOR_H
#define DYNET_TENSOR_H

#include <initializer_list>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "dynet/dim.hpp"
#include "dynet/except.hpp"
#include "dynet/aligned-mem-pool.hpp"
#include "dynet/device-structs.hpp"

namespace dynet {

#define EIGEN_BACKEND 1
typedef float real;

struct Tensor {
    Tensor() : d(Dim()), v(nullptr), device(nullptr), mem_pool(DeviceMempool::NONE) {} //创建一个空的tensor
    Tensor(const Dim& d, float* v, Device* dev, DeviceMempool mem) : d(d), v(v), device(dev), mem_pool(mem) {}
    /**
     * 得到batch的pointer
     * \param bid 自己指定的batch id
     * \return 返回一个指针, 这个指针指向这些id的数字
    */
    float* batch_ptr(unsigned int bid) {
        //其中的batch_size是一个batch数量的所有维度进行相乘
        //假设我们的维度是{224,224,3}, 然后我们的Batch=32, 也就是32个{224,224,3}的数据, 那么对应的bid就是(0~31)
        //假设我们想要返回一个第9个batch的id, 那么第9个的{224,224,3}: (9 % 32) * (一个batch的所有维度相乘) + v
        //这里的v是nullptr或者是自己指定的v
        return v + (bid % d.bd) * d.batch_size(); 
    }
    //这里重载了batch_ptr, 是为了不让用户随意更改对应的值。
    const float* batch_ptr(unsigned int bid) const {
        return v + (bid % d.bd) * d.batch_size();
    }
    // 检查是否有Nan或者是无穷的数
    bool is_valid() const;
    
    /**
     * 获取一个batch的Tensor对象
     * 如果tensor只有一个维度,就会进行broadcast, 否则的话我们检查需求的batch是否小于所有的batch
     * \param b Batch id
     * \return 返回一个batch_id 对应的tensor
    */
    Tensor batch_elem(unsigned int b) const {
        if (d.batch_elems() == 1) {
            return *this;
        } else {
            if (b >= d.batch_elems()) {
                std::stringstream ss;
                ss << "Requested batch id " << b << " is greater than the number of batch " << d.batch_elems();
                throw std::runtime_error(ss.str());
            }
            const unsigned int bsize = d.batch_size();
            // 这个是调用默认的拷贝构造函数吗, 确实是调用的是默认的拷贝构造函数, 这个拷贝构造函数没有主动定义
            // 因为这里的batch_elem是const修饰,也就是无法改变d对象的内容, 所以只能是新建一个new_d来返回
            Dim new_d(d) ; new_d.bd = 1; 
            Tensor ret(new_d, v + bsize * b, device, mem_pool);
            return ret;
        }
    }

    /**
     * \brief 获取所有batch tensor
     * \return 返回的是一个vector of tensor 
    */
    std::vector<Tensor> batch_elems() const {
        if (d.batch_elems() == 1) {
            return std::vector<Tensor>(1, *this);
        } else {
            //创建一个vector, batch_elems返回的是nd, 假设Dim d({224,224,3}, 32), 那么这里的bs就是32个tensor元素, 但是每一个元素是什么现在还是未知的
            std::vector<Tensor> bs(d.batch_elems());
            unsigned int bsize = d.batch_size(); // batch_size就是所有的维度相乘,假设是{224,224,3}, 那么就是224*224*3
            Dim new_d = d; new_d.bd = 1; // 因为这个是被const修饰过的函数, 所以原本的d(也就是成员函数)就不能再更改了, 所以创建一个新的
            for (unsigned int b = 0; b < d.batch_elems(); ++b) {
                bs[b] = Tensor(new_d, v + bsize * b, device, mem_pool);
            }
            return bs;
        }
    }

    Dim d;
    float* v;
    Device* device;
    DeviceMempool mem_pool;
};

//重载了<<
std::ostream& operator<<(std::ostream& os, const Tensor& t);
//得到一个元素的tensor, 比如这个tensor只有一个元素了, 我们就把这个取出来
real as_scalar(const Tensor& t);
//这个是把一个tensor给拉直, 不管是什么维度的
std::vector<real> as_vector(const Tensor& t);
//目前不知道
std::vector<real> as_scale_vector(const Tensor& v, float a);

struct TensorTools {
    /**
     * \brief Clip the values in the tensor to a fixed range
     * \param d Tensor to modify
     * \param left Target minimum value
     * \param right Target maximum value
     */
    static void clip(Tensor& d, float left, float right);
    /**
     * \brief Do an elementwise linear transform of values a*x + b
     * \
     */ 
    static void scale(Tensor& x, float left, float right);

};

}
#endif 