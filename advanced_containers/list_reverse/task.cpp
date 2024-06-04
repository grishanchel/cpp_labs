#include "task.h"

void ReverseList(std::list<int>& l) {
    int n = l.size();
    std::list<int> noviy;
    for(int i = 0; i<n ; i++){

        noviy.push_back(l.back());
        l.pop_back();
    }
    l.swap(noviy);
}