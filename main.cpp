#include <iostream>
#include "FrontEnd.h"
#include "HeapSort.h"
#include "extractSongs.h"
using namespace std;

int main() {
    //extracting top songs in the world as of August 1st, 2024 from a .csv file
    vector<pair<int, string>> arr = extractTopSongs((string &) "files/universal_top_spotify_songs.csv");
    HeapDataStructure test;
    test.HeapSort(arr);

    vector<pair<string, string>> song_data;
    song_data = ConvertVec(arr);

    WriteToFile(song_data);

    CreateHomeScreen();

    return 0;
}