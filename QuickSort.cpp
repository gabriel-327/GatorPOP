//
// Created by Srividya Donthineni on 8/1/24.
//

#include "QuickSort.h"
#include <vector>
#include <string>

using namespace std;

void QuickSort::PairSwap(pair<int, string> &one, pair<int, string> &two) {
    pair<int, string> holder = one;
    one = two;
    two = holder;
}

int QuickSort::Partition(vector<pair<int, string>> &vec, int low, int high) {
    int pivot = vec[high].first; // Pivot element
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        if (vec[j].first < pivot) { // Change to > for descending order
            i++;
            PairSwap(vec[i], vec[j]);
        }
    }
    PairSwap(vec[i + 1], vec[high]);
    return i + 1;
}

void QuickSort::QuickSortAlgorithm(vector<pair<int, string>> &vec, int low, int high) {
    if (low < high) {
        int pi = Partition(vec, low, high);

        QuickSortAlgorithm(vec, low, pi - 1);
        QuickSortAlgorithm(vec, pi + 1, high);
    }
}

void QuickSort::Sort(vector<pair<int, string>> &vec) {
    QuickSortAlgorithm(vec, 0, vec.size() - 1);
}
