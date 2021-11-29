#include "dynet/init.hpp"
#include <iostream>

using namespace std;
namespace dynet {
//NOTE:这里使用的是初始化参数列表进行赋值
DynetParams::DynetParams() : random_seed(0), mem_descriptor("512"), shared_parameters(false) {
    
} 
DynetParams::~DynetParams() {
    
}

DynetParams extract_dynet_params(int& argc, char **&argv, bool shared_parameters=false) {
    /**
     * @brief: 在这里先提取从命令行传进来的参数, 然后进行初始化
     * @argc: int, 参数的个数, 默认是1
     * @argv: vector, 参数的个数
     */
    DynetParams params;
    params.shared_parameters = shared_parameters;

    return params;
}

} //*namespace dynet*//