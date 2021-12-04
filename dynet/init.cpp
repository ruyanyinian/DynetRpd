#include "init.hpp"
#include <iostream>

using namespace std;
namespace dynet {
//NOTE:这里使用的是初始化参数列表进行赋值
DynetParams::DynetParams() : random_seed(0), mem_descriptor("512"), shared_parameters(false) {
    
} 
DynetParams::~DynetParams() {
    
}

//NOTE: 我们不能既在函数声明中声明默认参数又在函数定义中定义默认参数,通常我们只是在声明中定义默认参数即可
DynetParams extract_dynet_params(int& argc, char **&argv, bool shared_parameters) {
    /**
     * @brief: 在这里先提取从命令行传进来的参数, 然后进行初始化
     * @argc: int, 参数的个数, 默认是1
     * @argv: vector, 参数的个数
     */
    DynetParams params;
    params.shared_parameters = shared_parameters;

    return params;
}


void initialize(DynetParams& params) {
     /**
      * @brief 对params传入进来的参数进行初始化, 比如对一些device, randomseed等等进行初始化, 
      */
}

void initialize(int& argc, char **&argv, bool shared_parameters) { 
    /**
     * @brief 这个函数负责把extract_dynet_params和初始化串联起来
     */
    DynetParams params = extract_dynet_params(argc, argv, shared_parameters);
    initialize(params);
}

} //*namespace dynet*//