#pragma once

#include "ButtonView.h"
#include "config.h"
#include "utils/activity/ActivityManager.h"
#include "utils/activity/Activity.h"
#include "RenderWindowDI.h"

class GameOverActivity : public Activity {
    Injected<sf::RenderWindow> window;
    Injected<ActivityManager> activityManager;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape backgroundMask;

    sf::Texture gameOverImageTexture;
    sf::Sprite gameOverImageSprite;

    ButtonView restartButton;
    ButtonView exitButton;

public:
    GameOverActivity();

    void restart();

    void exit();

    void handleState() override;

    void handleEvent(sf::Event & event) override;

    void update(float time) override;

    void draw(float time) override;
};