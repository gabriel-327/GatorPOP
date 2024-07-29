#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
// Define class etc


void SetText(sf::Text &text, float x, float y);
int CreateHomeScreen();
void CreateChart(sf::Font welcome_font);
vector<string> ReadFile();
void WriteToFile(vector<pair<string, string>> song_data);