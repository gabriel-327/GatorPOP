//
// Created by Srividya Donthineni on 8/1/24.
//

#ifndef GATORPOP_HASHMAP_H
#define GATORPOP_HASHMAP_H
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;


class HashMap {
private:
    unordered_map<string, string> RetrieveSongsFromYear(const vector<pair<int, string>>& song_data, int year);
    void DisplayBottom50Songs(unordered_map<string, string>& song_map);
};


#endif //GATORPOP_HASHMAP_H
