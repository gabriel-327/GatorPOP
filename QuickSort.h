//
// Created by Srividya Donthineni on 8/1/24.
//

#ifndef GATORPOP_QUICKSORT_H
#define GATORPOP_QUICKSORT_H
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//needed to add change to commit
class QuickSort {
public:
    void PairSwap(std::pair<int, std::string> &one, std::pair<int, std::string> &two);
    void QuickSortAlgorithm(std::vector<std::pair<int, std::string>> &vec, int low, int high);
    int Partition(std::vector<std::pair<int, std::string>> &vec, int low, int high);
    void Sort(std::vector<std::pair<int, std::string>> &vec);
};


#endif //GATORPOP_QUICKSORT_H
