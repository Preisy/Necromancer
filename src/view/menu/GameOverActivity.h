#pragma once

#include "MenuActivity.h"
#include "utils/activity/ActivityManager.h"

class GameOverActivity : public MenuActivity {
    Injected<ActivityManager> activityManager;

    sf::Texture gameOverImageTexture;
    sf::Sprite gameOverImageSprite;

    ButtonView restartButton;
    ButtonView exitButton;

public:
    GameOverActivity();

private:
    void start();

    void exit();

public:
    void handleState() override;

    void handleEvent(sf::Event & event) override;

    void draw(float time) override;
};