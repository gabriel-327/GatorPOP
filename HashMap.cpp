//
// Created by Srividya Donthineni on 8/1/24.
//

#include "HashMap.h"
using namespace std;

unordered_map<string, string> HashMap::RetrieveSongsFromYear(const vector<pair<int, std::string>> &song_data, int year) {
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

void HashMap::DisplayBottom50Songs(unordered_map<std::string, std::string> &song_map) {
    vector<string> keys;
    for (const auto& song : song_map) {
        keys.push_back(song.first);
    }

    sort(keys.begin(), keys.end());

    int count = 0;
    for (const auto& key : keys) {
        cout << key << ": " << song_map[key] << endl;
        if (++count >= 50) {
            break;
        }
    }
}

void HashMap::SortAndDisplaySongs(const vector<pair<int, string>> &song_data) {
    // converting song data to a vector of pairs
    vector<pair<int, string>> songs = song_data;

    // sorting the songs by year
    sort(songs.begin(), songs.end());

    // displaying the bottom 50 songs
    int count = 0;
    for (const auto& song : songs) {
        cout << song.first << ": " << song.second << endl;
        if (count++ >= 50) {
            break;
        }
    }
}
