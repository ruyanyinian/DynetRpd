#ifndef DYNET_TENSOR_EIGEN_HPP
#define DYNET_TENSOR_EIGEN_HPP

// This file includes all of the DyNet tensor functions that require
// Eigen to be importet.d. 

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


}
#endif
