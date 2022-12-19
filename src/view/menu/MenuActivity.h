#pragma once

#include "ButtonView.h"
#include "config.h"
#include "utils/activity/Activity.h"
#include "RenderWindowDI.h"

class MenuActivity : public Activity {
protected:
    Injected<sf::RenderWindow> window;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape backgroundMask;

public:
    MenuActivity();

    void handleState() override;

    void handleEvent(sf::Event & event) override;

    void update(float time) override;

    void draw(float time) override;
};