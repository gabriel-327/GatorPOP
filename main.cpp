#include <iostream>
#include "FrontEnd.h"
#include "HeapSort.h"
#include "HashMap.h"
#include "extractSongs.h"
using namespace std;


int main() {
    // add
    vector<pair<int, string> > arr;
    string filepath = "files/universal_top_spotify_songs.csv";
    arr = extractTopSongs(filepath);

    // Front end
    FrontEnd screen;

    // testing heapsort
    HeapDataStructure test;
    test.HeapSort(arr);


    //testing hashmap class
//    HashMap testHashMap;
//    testHashMap.SortAndDisplaySongs(arr);

    vector<pair<string, string>> song_data;
    song_data = screen.ConvertVec(arr);
    screen.WriteToFile(song_data);
    screen.CreateHomeScreen();
    return 0;
}