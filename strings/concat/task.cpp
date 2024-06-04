#include "task.h"
char* concat(const char* lhs, const char* rhs) {
    int l1 = 0;
    while (lhs[l1] != '\0') {
        l1++;
    }
    int l2 = 0;
    while (rhs[l2] != '\0') {
        l2++;
    }

    char* ptr_str = new char(l1 + l2 + 1);
    int d = 0;
    for (d = 0; d < l1; d++)
        ptr_str[d] = lhs[d];

    for (int v = 0; v < l2; v++) {
        ptr_str[d] = rhs[v];
        d++;
    }
    ptr_str[d] = '\0';
    return ptr_str;
}