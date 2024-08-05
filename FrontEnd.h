#ifndef FRONTEND_H
#define FRONTEND_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

void SetText(sf::Text &text, float x, float y);
int CreateHomeScreen();
void CreateChart(sf::Font welcome_font);
std::vector<std::string> ReadFile();
void WriteToFile(std::vector<std::pair<std::string, std::string>> &song_data);
std::vector<std::pair<std::string, std::string>> ConvertVec(std::vector<std::pair<int, std::string>> &raw_data);

#endif // FRONTEND_H
