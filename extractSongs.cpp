//
// Created by Shashank Navale on 8/3/24.
//

#include "extractSongs.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>

using namespace std;

int dateFormatter(const std::string &dateString) {
    int year, month, day;
    char delim;

    stringstream ss(dateString);
    ss >> month >> delim >> day >> delim >> year;

    if (year < 100) {
        year += (year <= 24) ? 2000 : 1900;
    }


    stringstream formattedVersion;
    formattedVersion << setw(4) << setfill('0') << year <<
                     setw(2) << setfill('0')
                     << month << setw(2) << setfill('0') << day;

    int formattedOutput;
    formattedVersion >> formattedOutput;
    return formattedOutput;
}

vector<pair<int, string> > extractTopSongs(string &filename) {
    fstream file(filename);
    unordered_set<string> uniqueSongsTracker;
    string currentLine;

    vector<pair<int, string>> data;

    if (!file.is_open()) {
        cerr << "Cannot open file" << endl;
        return data;
    }

    while (getline(file, currentLine) && uniqueSongsTracker.size() <= 50000) {
        stringstream ss(currentLine);
        string song, releaseDate;

        if (getline(ss, song, ',') && getline(ss, releaseDate)) {
            int formattedReleaseDate = dateFormatter(releaseDate);
            if (uniqueSongsTracker.find(song) == uniqueSongsTracker.end()) {
                if (formattedReleaseDate < 20240806) {
                    uniqueSongsTracker.insert(song);
                    data.push_back({dateFormatter(releaseDate), song});
                }
                else {
                    continue;
                }
            } else {
                continue;
            }
        }

    }
    file.close();
    return data;
}