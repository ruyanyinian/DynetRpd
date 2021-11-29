#ifndef DYNET_INIT_H
#define DYNET_INIT_H

#include <string>
#include <vector>

namespace dynet {
//QUESTION(QINYU): 为什么dynet的param需要定义成一个struct结构?
struct DynetParams {
    DynetParams(); /*dynetparams的初始化函数*/
    ~DynetParams(); /*dynetparams的析构函数*/
    unsigned int random_seed; /*随机种子的生成*/
    std::string mem_descriptor; /*整个网络需要的内存是多少*/
    bool shared_parameters;
};

DynetParams extract_dynet_params(int& argc, char **&argv, bool shared_parameters=false);
 
}
#endif