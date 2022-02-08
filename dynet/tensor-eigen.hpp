#ifndef DYNET_TENSOR_EIGEN_HPP
#define DYNET_TENSOR_EIGEN_HPP

// This file includes all of the DyNet tensor functions that require
// Eigen to be imported. 

#include "dynet/tensor.hpp"
#include <unsupported/Eigen/CXX11/Tensor>

namespace dynet {
	
inline Eigen::Map<Eigen::MatrixXf> mat(Tensor& t) {
	DYNET_ARG_CHECK((t.d.batch_elems() == 1 && t.d.ndims() < 3), 
	"Attempted to access Tensor with more than one batch element or more than two dimensions in matrix form: " << t.d);
	return Eigen::Map<Eigen::MatrixXf>(t.v, t.d.rows(), t.d.cols());
}

inline Eigen::Map<Eigen::MatrixXf> mat(const Tensor& t) {
	return Eigen::Map<Eigen::MatrixXf>(t.v, t.d.rows(), t.d.cols());
} // 这个函数是对上面的函数的重载

inline Eigen::Map<Eigen::VectorXf> vec(Tensor& t) {
	return Eigen::Map<Eigen::VectorXf>(t.v, t.d.size());
}

inline const Eigen::Map<Eigen::VectorXf> vec(const Tensor & t) {
	return Eigen::Map<Eigen::VectorXf>(t.v, t.d.size());
}

/**
 * \brief Get the data as an order 1 Eigen tensor
 * \details this returns the full tensor contents as a one dimensional Eigen tensor which can be used for on-device processing where dimensions aren't important
 * \return Eigen order 1 tensor
 */

inline Eigen::TensorMap<Eigen::Tensor<float, 1>> tvec(Tensor& t) {
	return Eigen::TensorMap<Eigen::Tensor<float, 1>>(t.v, t.d.size());
}

inline const Eigen::TensorMap<Eigen::Tensor<float, 1>> tvec(const Tensor & t) {
  	return Eigen::TensorMap<Eigen::Tensor<float, 1>>(t.v, t.d.size());
}

inline Eigen::TensorMap<Eigen::Tensor<float, 2>> tbvec(Tensor& t) {
	return Eigen::TensorMap<Eigen::Tensor<float, 2>>(t.v, t.d.batch_size(), t.d.batch_elems());
}

inline const Eigen::TensorMap<Eigen::Tensor<float, 2>> tbvec(const Tensor & t) {
  return Eigen::TensorMap<Eigen::Tensor<float, 2>>(t.v, t.d.batch_size(), t.d.batch_elems());
}


template <int Order> inline Eigen::TensorMap<Eigen::Tensor<float, Order>> t(Tensor& t); // 声明一个主模板
// 声明一个重载函数, 重载上面的函数, 注意函数重载返回值不能作为判断条件。这里发生重载主要是参数的类型不同
template <int Order> inline const Eigen::TensorMap<Eigen::Tensor<float, Order>> t(const Tensor & t); 

// 对模板的一次全特化扩充。
template <> inline Eigen::TensorMap<Eigen::Tensor<float, 0>> t<0>(Tensor& t) {
	DYNET_ASSERT(t.d.batch_elems() == 1 && t.d.size() == 1, "Illegal access of tensor in function t<0>(Tensor & t): dim=" << t.d);
	return Eigen::TensorMap<Eigen::Tensor<float, 0>>(t.v);
}

}
#endif
