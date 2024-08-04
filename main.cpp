#include <iostream>
#include "FrontEnd.h"
#include "HeapSort.h"
#include "HashMap.h"

using namespace std;

int main() {
    //used for testing
    vector<pair<int, string>> arr = {
            {1975, "Bohemian Rhapsody"},
            {2017, "Shape of You"},
            {1983, "Billie Jean"},
            {1991, "Smells Like Teen Spirit"},
            {2010, "Rolling in the Deep"},
            {1965, "Like a Rolling Stone"},
            {2014, "Uptown Funk"},
            {1976, "Hotel California"},
            {1988, "Sweet Child O' Mine"},
            {1971, "Imagine"},
            {2019, "Bad Guy"}
    };
    //HeapDataStructure test;
    //test.HeapSort(arr);

    HashMap testHashMap;
    testHashMap.SortAndDisplaySongs(arr);

    vector<pair<string, string>> song_data;
    song_data = ConvertVec(arr);

    WriteToFile(song_data);

    CreateHomeScreen();

    return 0;
}