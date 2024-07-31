#pragma once
#include <vector>
#include <iostream>
using namespace std;

// Heapsort Implementation
class HeapDataStructure{
private:
    // Consider making a private variable the song data
    void MaxHeap(vector<pair<int, string>> &heap_vec, int heapsize);

    void Heapify(vector<pair<int, string>> &heap_vec, int heapsize, int root);

    void PairSwap(pair<int, string>& one, pair<int, string>& two);



public:
    void HeapSort(vector<pair<int, string>> &heap_vec);

};
