
#include <unsupported/Eigen/CXX11/Tensor>
#include <iostream>
using namespace std;
using namespace Eigen;



int main() {
    Eigen::Tensor<int, 1> a(5);
    a.setValues({ 1, 2, 3, 4, 5 });
    Eigen::Tensor<int, 1> b = a.cwiseMax(3);
    std::cout << b << std::endl;
}