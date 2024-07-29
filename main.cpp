#include <iostream>
#include "FrontEnd.h"
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    vector<pair<string, string>> song_data;
    for(int i = 0; i < 10; i++){
        // Using to see if it will write data, we need to find a way to write our top 10 spotify data
        std::string player = "Year:" + to_string(i + 2000);
        std::string score = std::to_string(1000 - i * 100);
        song_data.push_back({player, score});

    }
    WriteToFile(song_data);
    CreateHomeScreen();
    return 0;
}
