#pragma once

#include "MenuActivity.h"
#include "utils/activity/ActivityManager.h"


class MainMenuActivity : public MenuActivity {
    Injected<ActivityManager> activityManager;

    sf::Texture gameOverImageTexture;
    sf::Sprite gameOverImageSprite;

    ButtonView startButton;
    ButtonView exitButton;

public:
    MainMenuActivity();

private:
    void continueGame();

    void restart();

    void exit();

public:
    void handleState() override;

    void handleEvent(sf::Event & event) override;

    void draw(float time) override;
};