#include "dynet/init.hpp"
#include <iostream>
using namespace std;
using namespace dynet;


int main(int argc, char** argv) {
    
    dynet::initialize(argc, argv);
    return 0;
}