#include "task.h"
#include <vector>

using namespace std;

void Swap(std::vector<int>& vHeap, std::vector<int>::size_type i, std::vector<int>::size_type j)
{
    if(i == j)
        return;

    int temp;
    temp = vHeap[i];
    vHeap[i] = vHeap[j];
    vHeap[j] = temp;
}

void Sift(std::vector<int>& vHeap, const std::vector<int>::size_type heapSize, const std::vector<int>::size_type siftNode)
{
    std::vector<int>::size_type i, j;

    j = siftNode;
    do
    {
        i = j;
        if(((2*i + 1) < heapSize) && vHeap[j] < vHeap[2*i + 1])
            j = 2*i + 1;
        if(((2*i + 2) < heapSize) && vHeap[j] < vHeap[2*i + 2])
            j = 2*i + 2;

        Swap(vHeap, i, j);
    }
    while(i != j);
}

void MakeInitialHeap(std::vector<int>& vHeap)
{
    for(int i = vHeap.size() - 1; i >= 0; --i)
    {
        Sift(vHeap, vHeap.size(), i);
    }
}


vector<int> HeapSort(const vector<int>& v) {
    vector<int> new_vec=v;
    MakeInitialHeap(new_vec);
    for(std::vector<int>::size_type i = new_vec.size()-1; i > 0; --i)
    {
        Swap(new_vec, i, 0);
        Sift(new_vec, i, 0);
    }
    return new_vec;
}



