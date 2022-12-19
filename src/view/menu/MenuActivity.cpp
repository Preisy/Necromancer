#include "MenuActivity.h"



MenuActivity::MenuActivity() {
    backgroundTexture.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\game_over_background.png)");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundMask.setFillColor(sf::Color(0x00000088));
    backgroundMask.setPosition(0, 0);
    backgroundMask.setSize({windowWidth, windowHeight});
}

void MenuActivity::handleState() {}

void MenuActivity::handleEvent(sf::Event & event) {}

void MenuActivity::update(float time) {}

void MenuActivity::draw(float time) {
    window->draw(backgroundSprite);
    window->draw(backgroundMask);
}

