#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}


int main() {
    int width = 1024;
    int height = 768;
    // Creates window
    sf:: RenderWindow window(sf::VideoMode(width, height), "GATOR POP");
    // Gets necessary font
    sf::Font welcome_font;

    // Creates welcome text
    sf::Text welcome_text("WELCOME TO GATOR POP!", welcome_font, 60);
    welcome_text.setFillColor(sf::Color::Black);
    welcome_text.setStyle(sf::Text::Bold);
    setText(welcome_text, 125, 100);

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
    buttonSprite.setPosition((float)440, (float) 350);


    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(buttonSprite.getGlobalBounds().contains({(float)event.mouseButton.x, (float)event.mouseButton.y})){
                cout << "Button Clicked" << endl;
            }

        }
        // Window color and text
        window.clear(sf::Color(208,240,192));
        window.draw(welcome_text);


        window.draw(buttonSprite);

        window.display();
    }

    return 0;
}
