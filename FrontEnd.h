#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;

class FrontEnd{
public:
    // Function used to handle opening the screen
    void CreateHomeScreen();
    // Writes to txt file
    void WriteToFile(vector<pair<string, string>> &song_data);
    // Converts to something that can be easily written to file
    vector<pair<string, string>> ConvertVec(vector<pair<int, string>> &raw_data);
    // Constructor
    FrontEnd(){
        this->orange_button_on = false;
        this->blue_button_on = false;
    }


private:
    bool orange_button_on;
    bool blue_button_on;
    // Helper functions for create home screen
    void SetText(sf::Text &text, float x, float y);
    void CreateChart(sf::Font welcome_font);
    vector<string> ReadFile();
    string formatDate(string& date);

};
