#include "FrontEnd.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

void SetText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int CreateHomeScreen() {
    int width = 1024;
    int height = 768;
    // Creates window
    sf::RenderWindow window(sf::VideoMode(width, height), "GATOR POP");
    // Gets necessary font
    sf::Font welcome_font;

    // Creates welcome text
    sf::Text welcome_text("WELCOME TO GATOR POP!", welcome_font, 60);
    welcome_text.setFillColor(sf::Color::Black);
    welcome_text.setStyle(sf::Text::Bold);
    SetText(welcome_text, 125, 100);

    // Button Sprites
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("files/images/Generate Button.png")) {
        // Handle loading error
        return -1;
    }

    if (!welcome_font.loadFromFile(
            "files/font.ttf")) {
        cout << "not working" << endl;
    }

    sf::Sprite buttonSprite;
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition((float) 440, (float) 350);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Dev shortcut, push key to close
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
                window.close();
            }
            if (buttonSprite.getGlobalBounds().contains({(float) event.mouseButton.x, (float) event.mouseButton.y})) {
                CreateChart(welcome_font);
//                cout << "Button Clicked" << endl;
            }

        }
        // Window color and text
        window.clear(sf::Color(208, 240, 192));
        window.draw(welcome_text);


        window.draw(buttonSprite);

        window.display();
    }
}

void CreateChart(sf::Font welcome_font)
{

    sf::RenderWindow leaderboard_window(sf::VideoMode(1024,768), "Playlist");

    sf::Text leaderboard_text("Hello What Do We Want To Say Here", welcome_font, 20);
    leaderboard_text.setFillColor(sf::Color::Black);
    leaderboard_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    SetText(leaderboard_text, 512, 100);

    string all_names;
    vector<string> leaderboard_vec;
    leaderboard_vec = ReadFile();
    for (int i = 0; i < leaderboard_vec.size(); i += 2) {
        int num_place = i / 2 + 1;
        all_names += to_string(num_place) + ".\t" + leaderboard_vec[i] + "\t" + leaderboard_vec[i + 1] + "\n\n";
    }

    sf::Text player_data;
    player_data.setString(all_names);
    player_data.setFont(welcome_font);
    player_data.setCharacterSize(18);
    player_data.setFillColor(sf::Color::Black);
    player_data.setStyle(sf::Text::Bold);
    SetText(player_data, 512, 400);


    while (leaderboard_window.isOpen()) {
        sf::Event event;
        while (leaderboard_window.pollEvent(event)) {
            // Short cut
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
                leaderboard_window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
            }
        }
        // colors light grey = 211, 211, 211
        leaderboard_window.clear(sf::Color(211, 211, 211));
        leaderboard_window.draw(leaderboard_text);
        leaderboard_window.draw(player_data);
        leaderboard_window.display();

    }
}

vector<string> ReadFile() {
    ifstream readleaderboard;
    readleaderboard.open("files/leaderboard.txt");

    string temp;
    vector<string> leaderboard_vec;
    while(readleaderboard) {
        getline(readleaderboard, temp, ',');
        leaderboard_vec.push_back(temp);
        getline(readleaderboard, temp, '\n');
        leaderboard_vec.push_back(temp);
    }
    readleaderboard.close();
    // not necessary
    for (const auto& element : leaderboard_vec) {
        // Print the current element
        std::cout << element << std::endl;
    }
    return leaderboard_vec;
}

void WriteToFile(vector<pair<string, string>> song_data) {
    ofstream write_to_file;
    write_to_file.open("files/leaderboard.txt");
    for(auto& entry : song_data){
        write_to_file << entry.first << ", " << entry.second << "\n";
    }
    write_to_file.close();
}
