#include "FrontEnd.h"
#include "HeapSort.h"
#include "HashMap.h"
#include "extractSongs.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


string FrontEnd::formatDate(string& date) {
    // Changes only the date
    if (date.size() != 8) return date;
    // Places the dashes into correct spot
    return date.substr(0, 4) + "-" + date.substr(4, 2) + "-" + date.substr(6, 2);
}

void FrontEnd::SetText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void FrontEnd::CreateHomeScreen() {
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
        return;
    }

    if (!welcome_font.loadFromFile("files/font.ttf")) {
        cout << "not working" << endl;
    }

    sf::Texture buttonBlueTexture;
    if (!buttonBlueTexture.loadFromFile("files/images/GenerateButtonBlue.png")) {
        return;
    }

    sf::Sprite buttonSprite;
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition((float) 350, (float) 359);

    sf::Sprite buttonSpriteTwo;
    buttonSpriteTwo.setTexture(buttonBlueTexture);
    buttonSpriteTwo.setPosition((float) 550, (float) 359);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (buttonSprite.getGlobalBounds().contains({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
                    orange_button_on = !orange_button_on;
                    CreateChart(welcome_font);
                }
                else if (buttonSpriteTwo.getGlobalBounds().contains({ (float)event.mouseButton.x, (float)event.mouseButton.y })) {
                    blue_button_on = !blue_button_on;
                    CreateChart(welcome_font);
                }
            }

        }

        window.clear(sf::Color(208, 240, 192));
        window.draw(welcome_text);
        window.draw(buttonSprite);
        window.draw(buttonSpriteTwo);
        window.display();
    }
}

void FrontEnd::CreateChart(sf::Font welcome_font) {
    if(orange_button_on) {
        vector<pair<int, string> > arr;
        string filepath = "files/universal_top_spotify_songs.csv";
        arr = extractTopSongs(filepath);
        HeapDataStructure heap;
        heap.HeapSort(arr);
        vector<pair<string, string>> song_data;
        song_data = ConvertVec(arr);
        WriteToFile(song_data);
    }
//    else if(blue_button_on){
//        vector<pair<int, string> > arr;
//        string filepath = "files/universal_top_spotify_songs.csv";
//        arr = extractTopSongs(filepath);
//        HashMap testHashMap;
//        testHashMap.SortAndDisplaySongs(arr);
//        vector<pair<string, string>> song_data;
//        song_data = ConvertVec(arr);
//        WriteToFile(song_data);
//    }
    sf::RenderWindow leaderboard_window(sf::VideoMode(1024, 768), "Ranked Song");

    // Header Text
    sf::Text leaderboard_text("Songs Ranked By Release Date", welcome_font, 20);
    leaderboard_text.setFillColor(sf::Color::Black);
    leaderboard_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    SetText(leaderboard_text, 512, 50);

    // Song list text
    string all_names;
    vector<string> leaderboard_vec = ReadFile();
    for (int i = 0; i < leaderboard_vec.size() - 1; i += 2) {
        int num_place = i / 2 + 1;
        string formattedDate = formatDate(leaderboard_vec[i]);

        if(num_place < 10){
            all_names += to_string(num_place) + ".     " + formattedDate + "\t" + leaderboard_vec[i + 1] + "\n\n";
        }
        else{
            all_names += to_string(num_place) + ".    " + formattedDate + "\t" + leaderboard_vec[i + 1] + "\n\n";
        }
    }

    sf::Text music_data;
    music_data.setString(all_names);
    music_data.setFont(welcome_font);
    music_data.setCharacterSize(18);
    music_data.setFillColor(sf::Color::Black);
    music_data.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = music_data.getLocalBounds();
    music_data.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
    music_data.setPosition(512, 100); // Centered horizontally, below the header

    // View for scrolling content
    sf::View contentView(sf::FloatRect(0, 100, 1024, 668)); // Leave space for the header
    contentView.setViewport(sf::FloatRect(0, 100.f / 768, 1, 668.f / 768));

    float scroll_speed = 50.0f;

    while (leaderboard_window.isOpen()) {
        sf::Event event;
        while (leaderboard_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboard_window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    contentView.move(0, -scroll_speed);
                } else {
                    contentView.move(0, scroll_speed);
                }
                leaderboard_window.setView(contentView);
            }
        }

        leaderboard_window.clear(sf::Color(211, 211, 211));
        leaderboard_window.setView(leaderboard_window.getDefaultView()); // Set view for static header
        leaderboard_window.draw(leaderboard_text);
        leaderboard_window.setView(contentView); // Set view for scrolling content
        leaderboard_window.draw(music_data);
        leaderboard_window.display();
    }
}

vector<string> FrontEnd::ReadFile() {
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

void FrontEnd::WriteToFile(vector<pair<string, string>> &song_data) {
    ofstream write_to_file("files/leaderboard.txt");
    int size = song_data.size();
    int start_index = max(0, size - 50);
    for (int i = size - 1; i >= start_index; --i) {
        write_to_file << song_data[i].first << ", " << song_data[i].second << "\n";
    }
}

vector<pair<string, string>> FrontEnd::ConvertVec(vector<pair<int, string>> &raw_data) {
    vector<pair<string, string>> song_data;
    for (const auto &data : raw_data) {
        string date = to_string(data.first);
        string song = data.second;
        song_data.push_back({ date, song });
    }
    return song_data;
}
