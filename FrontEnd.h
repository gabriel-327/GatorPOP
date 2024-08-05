#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;

class FrontEnd{
public:
    void CreateHomeScreen();
    void WriteToFile(vector<pair<string, string>> &song_data);
    vector<pair<string, string>> ConvertVec(vector<pair<int, string>> &raw_data);


private:
    void SetText(sf::Text &text, float x, float y);
    void CreateChart(sf::Font welcome_font);
    vector<string> ReadFile();
    string formatDate(string& date);
};
