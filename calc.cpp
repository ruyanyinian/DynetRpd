#include "calc.hpp"

namespace computation {
#if EXEC_ADD
int add(int a, int b) {
    return a + b;
}
#else
int sub(int a, int b) {
    return a - b;
}
#endif

}