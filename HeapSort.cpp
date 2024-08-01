#include "HeapSort.h"
#include <iostream>
#include <vector>
using namespace std;


void HeapDataStructure::PairSwap(pair<int, string> &one, pair<int, string> &two) {
    pair<int, string> holder = one;
    one = two;
    two = holder;
}


// Heap functions used https://www.geeksforgeeks.org/building-heap-from-array/ as guidance to create them
void HeapDataStructure::Heapify(vector<pair<int, string>> &heap_vec, int heapsize, int root){
    int largest_value = root;
    int left_branch = 2 * root + 1;
    int right_branch = 2* root + 2;

    // If left child larger than the root
    if(left_branch < heapsize && heap_vec[left_branch].first > heap_vec[largest_value].first){
        largest_value = left_branch;
    }

    // If right child larger than largest
    if(right_branch < heapsize && heap_vec[right_branch].first > heap_vec[largest_value].first){
        largest_value = right_branch;
    }

    // If largest value is not the root
    if(largest_value != root){
        PairSwap(heap_vec[root], heap_vec[largest_value]);

        // Recursively heapify
        Heapify(heap_vec, heapsize, largest_value);
    }
}

void HeapDataStructure::MaxHeap(vector<pair<int, string>> &heap_vec, int heapsize) {
    // Index of last lead node
    int first_index = (heapsize/2) - 1;
    // Reverse level order traversal
    for(int i = first_index; i>= 0; i--){
        Heapify(heap_vec, heapsize, i);
    }

}

// Function built around Professor Aman's YouTube video "Heaps (5e): Heap Sort" : https://www.youtube.com/watch?v=bzR6hW8I6ao&list=PLvBZ6Nw3S6DQqWD5iiPGIWqFLiuRaQYC1&index=5
void HeapDataStructure::HeapSort(vector<pair<int, string>> &heap_vec) {
    int heapsize = heap_vec.size();
    // Build heap in place
    for (int i = heapsize / 2 - 1; i >= 0; i--)
        Heapify(heap_vec, heapsize, i);

    // Extract last element in heap
    for (int i = heapsize - 1; i >= 0; i--) {
        // Move current root to end
        swap(heap_vec[0], heap_vec[i]);

        // call max heapify on the reduced heap
        Heapify(heap_vec, i, 0);
    }

}