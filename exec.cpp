#include "dynet/dim.hpp"
using namespace std;
using namespace dynet;

int main() {
    dynet::Dim d({224, 224, 3});
    d.delete_dims({0,1}, false);
    std::cout << d << std::endl;
    return 0;
}