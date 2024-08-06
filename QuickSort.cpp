//
// Created by Srividya Donthineni on 8/1/24.
//

#include "QuickSort.h"
#include <vector>
#include <string>
using namespace std;

// function which swaps two pairs of <int, string>
void QuickSort::PairSwap(pair<int, string> &one, pair<int, string> &two) {
    pair<int, string> temp = one;
    one = two;
    two = temp;
}

//function to partition the vector around the pivot element
int QuickSort::Partition(vector<pair<int, string>> &vec, int low, int high) {
    int pivot = vec[high].first; //last element as the pivot
    int i = low - 1; //initializing the index of the smaller element

    // going through all the elements and rearrange them based on the pivot
    for (int j = low; j < high; j++) {
        // when the current element is smaller than the pivot, swap the current element with element i
        if (vec[j].first < pivot) {
            i++;
            PairSwap(vec[i], vec[j]);
        }
    }
    PairSwap(vec[i + 1], vec[high]); // swap pivot with element at i+1
    return i + 1;
}

//recursive function for QuickSort
void QuickSort::QuickSortAlgorithm(vector<pair<int, string>> &vec, int low, int high) {
    if (low < high) {
        int pi = Partition(vec, low, high);

        QuickSortAlgorithm(vec, low, pi - 1);
        QuickSortAlgorithm(vec, pi + 1, high);
    }
}

//public function to call from the frontEnd
void QuickSort::Sort(vector<pair<int, string>> &vec) {
    QuickSortAlgorithm(vec, 0, vec.size() - 1);
}
