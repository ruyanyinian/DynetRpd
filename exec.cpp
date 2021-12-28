
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


int main() {

    int num = 123;
    auto f = [&] { return num - 5; };
    num = 100;
    int res = f();
    std::cout << res << std::endl;
    return 0;
}