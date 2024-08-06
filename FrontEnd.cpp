#include "FrontEnd.h"
#include "HeapSort.h"
#include "extractSongs.h"
#include "QuickSort.h"
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
    // Places the text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void FrontEnd::CreateHomeScreen() {
    // Window size
    int width = 1024;
    int height = 768;
    sf::RenderWindow window(sf::VideoMode(width, height), "GATOR POP");
    sf::Font welcome_font;

    // Defines all features necessary for the text
    sf::Text welcome_text("WELCOME TO GATOR POP!", welcome_font, 60);
    welcome_text.setFillColor(sf::Color::Black);
    welcome_text.setStyle(sf::Text::Bold);
    SetText(welcome_text, 125, 100);

    // Text to go above orange button
    sf::Text heap_text("Heap Sort", welcome_font, 30);
    heap_text.setFillColor(sf::Color::Black);
    SetText(heap_text, 340, 340);

    // Text to go above blue button
    sf::Text quicksort_text("Quick Sort", welcome_font, 30);
    quicksort_text.setFillColor(sf::Color::Black);
    SetText(quicksort_text, 540, 340);

    // Check for importing the button png
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("files/images/Generate Button.png")) {
        cout << "check file path for generate button" << endl;
        return;
    }
    sf::Texture buttonBlueTexture;
    if (!buttonBlueTexture.loadFromFile("files/images/GenerateButtonBlue.png")) {
        cout << "check file path for generate button" << endl;
        return;
    }

    // Check for the font importing
    if (!welcome_font.loadFromFile("files/font.ttf")) {
        cout << "font not importing correctly" << endl;
    }

    // Necessary calls from SFML to set the orange button
    sf::Sprite orangeSprite;
    orangeSprite.setTexture(buttonTexture);
    orangeSprite.setPosition((float) 350, (float) 359);

    // Necessary calls from SFML to set the blue button
    sf::Sprite blueSpriteTwo;
    blueSpriteTwo.setTexture(buttonBlueTexture);
    blueSpriteTwo.setPosition((float) 550, (float) 359);

    while (window.isOpen()) {
        // Handles input from the user
        sf::Event event;
        while (window.pollEvent(event)) {
            // Closes window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                // Handles when orange button is clicked by creating the chart and toggling orange on
                if (orangeSprite.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y })) {
                    orange_button_on = !orange_button_on;
                    CreateChart(welcome_font);
                }
                // Handles when blue button is clicked by creating the chart and toggling blue on
                else if (blueSpriteTwo.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y })) {
                    blue_button_on = !blue_button_on;
                    CreateChart(welcome_font);
                }
            }
        }

        // Draws all necessary text and sprites
        window.clear(sf::Color(208, 240, 192));
        window.draw(welcome_text);
        window.draw(heap_text);
        window.draw(quicksort_text);
        window.draw(orangeSprite);
        window.draw(blueSpriteTwo);
        window.display();
    }
}

void FrontEnd::CreateChart(sf::Font welcome_font) {
    // If orange button is clicked it gets the songs from our data set and uses the heap data structure and heapsort to write
    // most recent released songs
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
    // If blue button is clicked it gets the songs from our data set and uses the quick sort algorithm to sort and display
    // most recent released songs
    else if(blue_button_on){
        vector<pair<int, string> > arr;
        string filepath = "files/universal_top_spotify_songs.csv";
        arr = extractTopSongs(filepath);
        QuickSort Quicksort;
        Quicksort.Sort(arr);
        vector<pair<string, string>> song_data;
        song_data = ConvertVec(arr);
        WriteToFile(song_data);
    }
    // Creates window ranked songs
    sf::RenderWindow leaderboard_window(sf::VideoMode(1024, 768), "Ranked Song");

    // Header Text
    sf::Text leaderboard_text("Songs Ranked By Release Date", welcome_font, 20);
    leaderboard_text.setFillColor(sf::Color::Black);
    leaderboard_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    SetText(leaderboard_text, 512, 50);

    // Song list text
    string all_names;

    vector<string> leaderboard_vec = ReadFile();
    // Every two elements in the vector represent first a date and then a song name associated with it
    for (int i = 0; i < leaderboard_vec.size() - 1; i += 2) {
        int num_place = i / 2 + 1;
        // Formats date with dashes
        string formattedDate = formatDate(leaderboard_vec[i]);

        // This section handles the numbers being properly spaced when printed
        if(num_place < 10){
            // All string values are appended to a string variable which will be read and printed on the window
            all_names += to_string(num_place) + ".     " + formattedDate + "\t" + leaderboard_vec[i + 1] + "\n\n";
        }
        else{
            all_names += to_string(num_place) + ".    " + formattedDate + "\t" + leaderboard_vec[i + 1] + "\n\n";
        }
    }

    // Handles text for music data
    sf::Text music_data;
    music_data.setString(all_names);
    music_data.setFont(welcome_font);
    music_data.setCharacterSize(18);
    music_data.setFillColor(sf::Color::Black);
    music_data.setStyle(sf::Text::Bold);

    // Creates a box to help with centering the text in the page
    sf::FloatRect textRect = music_data.getLocalBounds();
    music_data.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
    music_data.setPosition(512, 100);

    // View for scrolling content
    // Leaves space so the header wont scroll
    sf::View contentView(sf::FloatRect(0, 100, 1024, 668));
    contentView.setViewport(sf::FloatRect(0, 100.f / 768, 1, 668.f / 768));

    float scroll_speed = 50.0f;

    // Event handling in chart window
    while (leaderboard_window.isOpen()) {
        sf::Event event;
        while (leaderboard_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboard_window.close();
            }
            // Handles scroll
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    contentView.move(0, -scroll_speed);
                } else {
                    contentView.move(0, scroll_speed);
                }
                leaderboard_window.setView(contentView);
            }
        }
        // Draws and sets for the scroll and the text
        leaderboard_window.clear(sf::Color(211, 211, 211));
        leaderboard_window.setView(leaderboard_window.getDefaultView());
        leaderboard_window.draw(leaderboard_text);
        leaderboard_window.setView(contentView);
        leaderboard_window.draw(music_data);
        leaderboard_window.display();
    }
}

// Takes the information in the leaderboard text file and puts it into a vector
vector<string> FrontEnd::ReadFile() {
    ifstream readleaderboard("files/leaderboard.txt");
    string temp;
    vector<string> leaderboard_vec;
    // Uses delimiters to read entries
    while (getline(readleaderboard, temp, ',')) {
        leaderboard_vec.push_back(temp);
        getline(readleaderboard, temp, '\n');
        leaderboard_vec.push_back(temp);
    }
    return leaderboard_vec;
}

// Takes the song data and writes the most recent 50 songs to leaderboard text file
void FrontEnd::WriteToFile(vector<pair<string, string>> &song_data) {
    ofstream write_to_file("files/leaderboard.txt");
    int size = song_data.size();
    int start_index = max(0, size - 50);
    // only gets the last 50 songs since it is sorted in descending order
    for (int i = size - 1; i >= start_index; --i) {
        write_to_file << song_data[i].first << ", " << song_data[i].second << "\n";
    }
}

// Changes a vector of pairs with types int and string to a vector of pairs of type string and string
vector<pair<string, string>> FrontEnd::ConvertVec(vector<pair<int, string>> &raw_data) {
    vector<pair<string, string>> song_data;
    for (auto &data : raw_data) {
        string date = to_string(data.first);
        string song = data.second;
        song_data.push_back({ date, song });
    }
    return song_data;
}
