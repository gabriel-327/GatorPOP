//
// Created by Srividya Donthineni on 8/1/24.
//

#include "HashMap.h"
#include <iostream>
#include <algorithm>

using namespace std;

unordered_map<string, string> HashMap::RetrieveSongsFromYear(const vector<pair<int, string>> &song_data, int year) {
    unordered_map<string, string> song_map;
    for (const auto& song : song_data) {
        int song_year = song.first;
        if (song_year == year) {
            string release_date = song.second.substr(0, 10); // Extracting release date
            string song_name = song.second.substr(11); // Extracting song name
            song_map[release_date] = song_name;
        }
    }
    return song_map;
}

void HashMap::DisplayBottom50Songs(unordered_map<string, string> &song_map) {
    vector<pair<string, string>> song_vector(song_map.begin(), song_map.end());

    // Sort the vector of pairs based on the release date in descending order
    sort(song_vector.begin(), song_vector.end(), [](const pair<string, string>& a, const pair<string, string>& b) {
        return a.first > b.first;
    });

    // Display the bottom 50 songs
    int count = 0;
    for (const auto& song : song_vector) {
        cout << song.first << ": " << song.second << endl;
        if (++count >= 50) {
            break;
        }
    }
}

void HashMap::SortAndDisplaySongs(const vector<pair<int, string>> &song_data) {
    // Copy the song data to a local vector
    vector<pair<int, string>> songs = song_data;

    // Sort the vector of pairs based on the year in descending order
    sort(songs.begin(), songs.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first > b.first;
    });

    // Display the bottom 50 songs
    int count = 0;
    for (const auto& song : songs) {
        cout << song.first << ": " << song.second << endl;
        if (count++ >= 50) {
            break;
        }
    }
}