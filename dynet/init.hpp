#ifndef DYNET_INIT_H
#define DYNET_INIT_H

#include <string>
#include <vector>

namespace dynet {
//QUESTION(QINYU): 为什么dynet的param需要定义成一个struct结构?
struct DynetParams {
    DynetParams(); /*dynetparams的初始化函数*/
    ~DynetParams(); /*dynetparams的析构函数*/
};
}
#endif