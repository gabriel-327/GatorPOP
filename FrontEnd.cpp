#include "FrontEnd.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void SetText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int CreateHomeScreen() {
    int width = 1024;
    int height = 768;
    sf::RenderWindow window(sf::VideoMode(width, height), "GATOR POP");
    sf::Font welcome_font;

    sf::Text welcome_text("WELCOME TO GATOR POP!", welcome_font, 60);
    welcome_text.setFillColor(sf::Color::Black);
    welcome_text.setStyle(sf::Text::Bold);
    SetText(welcome_text, 125, 100);

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("files/images/Generate Button.png")) {
        return -1;
    }

    if (!welcome_font.loadFromFile("files/font.ttf")) {
        cout << "not working" << endl;
    }

    sf::Sprite buttonSprite;
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition((float) 440, (float) 350);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (buttonSprite.getGlobalBounds().contains({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
                    CreateChart(welcome_font);
                }
            }
        }

        window.clear(sf::Color(208, 240, 192));
        window.draw(welcome_text);
        window.draw(buttonSprite);
        window.display();
    }

    return 0;
}

void CreateChart(sf::Font welcome_font) {
    sf::RenderWindow leaderboard_window(sf::VideoMode(1024, 768), "Playlist");

    sf::Text leaderboard_text("Songs Ranked By Release Date", welcome_font, 20);
    leaderboard_text.setFillColor(sf::Color::Black);
    leaderboard_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    SetText(leaderboard_text, 512, 50);

    string all_names;
    vector<string> leaderboard_vec = ReadFile();
    for (int i = 0; i < leaderboard_vec.size() - 2; i += 2) {
        int num_place = i / 2 + 1;
        if (num_place < 10) {
            all_names += to_string(num_place) + ".     " + leaderboard_vec[i] + "\t" + leaderboard_vec[i + 1] + "\n\n";
        }
        else {
            all_names += to_string(num_place) + ".    " + leaderboard_vec[i] + "\t" + leaderboard_vec[i + 1] + "\n\n";
        }
    }

    sf::Text player_data;
    player_data.setString(all_names);
    player_data.setFont(welcome_font);
    player_data.setCharacterSize(18);
    player_data.setFillColor(sf::Color::Black);
    player_data.setStyle(sf::Text::Bold);
    player_data.setPosition(512, 150); // Adjust initial position

    sf::View view = leaderboard_window.getView();
    float scroll_speed = 50.0f;

    while (leaderboard_window.isOpen()) {
        sf::Event event;
        while (leaderboard_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
                leaderboard_window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    view.move(0, -scroll_speed);
                }
                else {
                    view.move(0, scroll_speed);
                }
                leaderboard_window.setView(view);
            }
        }

        leaderboard_window.clear(sf::Color(211, 211, 211));
        leaderboard_window.draw(leaderboard_text);
        leaderboard_window.draw(player_data);
        leaderboard_window.display();
    }
}

vector<string> ReadFile() {
    ifstream readleaderboard("files/leaderboard.txt");
    string temp;
    vector<string> leaderboard_vec;
    while (getline(readleaderboard, temp, ',')) {
        leaderboard_vec.push_back(temp);
        getline(readleaderboard, temp, '\n');
        leaderboard_vec.push_back(temp);
    }
    return leaderboard_vec;
}

void WriteToFile(vector<pair<string, string>> &song_data) {
    ofstream write_to_file("files/leaderboard.txt");
    int size = song_data.size();
    int start_index = max(0, size - 50);
    for (int i = size - 1; i >= start_index; --i) {
        write_to_file << song_data[i].first << ", " << song_data[i].second << "\n";
    }
}

vector<pair<string, string>> ConvertVec(vector<pair<int, string>> &raw_data) {
    vector<pair<string, string>> song_data;
    for (const auto &data : raw_data) {
        string date = to_string(data.first);
        string song = data.second;
        song_data.push_back({ date, song });
    }
    return song_data;
}
