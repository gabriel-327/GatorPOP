#pragma once
#include <vector>
#include <iostream>
using namespace std;

// Heapsort Implementation
class HeapDataStructure{
private:
    void Heapify(vector<pair<int, string>> &heap_vec, int heapsize, int root);
    void PairSwap(pair<int, string>& one, pair<int, string>& two);
public:
    void HeapSort(vector<pair<int, string>> &heap_vec);

};
