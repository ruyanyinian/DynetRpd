#include "calc.hpp"
#include <stdio.h>
int main() {
#if EXEC_ADD
    int ans_add = computation::add(10, 3);
    printf("add %d\n", ans_add);
#else
    int ans_sub = computation::sub(10, 3);
    printf("sub %d\n", ans_sub);
#endif
    return 0;
}