#include "dynet/dim.hpp"
#include <iostream>
using namespace dynet;
int main() {

    dynet::Dim d({224, 224, 3});
    dynet::Dim t = d.signle_batch();
    std::cout << t.batch_size() << std::endl;
    return 0;
}