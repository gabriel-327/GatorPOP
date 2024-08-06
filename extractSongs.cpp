//
// Created by Shashank Navale on 8/3/24.
//
#include "extractSongs.h"
#include <iostream>
#include <iomanip>
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
    //get rid of the backslash delimiters and only store Year, Month, Day
    ss >> month >> delim >> day >> delim >> year;

    // add 2000 or 1000 depending on if the year is less than 24 or greater
    // to account for years in the 20th century
    if (year < 100) {
        year += (year <= 24) ? 2000 : 1900;
    }


    stringstream formattedVersion;
    // add zeros where necessary using stringstream
    formattedVersion << setw(4) << setfill('0') << year <<
                     setw(2) << setfill('0')
                     << month << setw(2) << setfill('0') << day;

    //convert formatted Output to int and concatenate together
    int formattedOutput;
    formattedVersion >> formattedOutput;
    return formattedOutput;
}

vector<pair<int, string> > extractTopSongs(string &filename) {
    fstream file(filename);
    unordered_set<string> uniqueSongsTracker; // unordered_set to keep track of unique song pairs
    string currentLine;

    // main data structure to hold extracted data
    vector<pair<int, string>> data;

    // raise errors if file does not open
    if (!file.is_open()) {
        cerr << "Cannot open file" << endl;
        return data;
    }
    // while loop runs until unique song tracker has collected enough unique song pairs
    while (getline(file, currentLine) && uniqueSongsTracker.size() <= 50000) {
        stringstream ss(currentLine);
        string song, releaseDate;

        // takes song name and release data seperated by a comma
        if (getline(ss, song, ',') && getline(ss, releaseDate)) {
            int formattedReleaseDate = dateFormatter(releaseDate);
            // checks if song pair is a duplicate using the set
            if (uniqueSongsTracker.find(song) == uniqueSongsTracker.end()) {
                // ensures all songs were released before August 6th 2024
                if (formattedReleaseDate < 20240806) {
                    //adds into set if not a duplicate
                    uniqueSongsTracker.insert(song);
                    data.push_back({dateFormatter(releaseDate), song});
                }
                // skips a song pair if the release date calculation is messed up
                else {
                    continue;
                }
                // skips song pair if it's a duplicate
            } else {
                continue;
            }
        }

    }
    file.close();
    return data;
}