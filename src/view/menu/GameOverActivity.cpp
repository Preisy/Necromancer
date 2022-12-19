#include "GameOverActivity.h"

#include "controller/FieldController.h"

GameOverActivity::GameOverActivity()
        : restartButton("Restart    ", [this]() { start(); }, 300),
          exitButton("Exit", [this]() { exit(); }, 400) {
    gameOverImageTexture.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\game_over_image.png)");
    gameOverImageSprite.setTexture(gameOverImageTexture);
    float k = float(0.5 * windowWidth) / (float) gameOverImageSprite.getTextureRect().width;
    gameOverImageSprite.setScale(k, k);

    gameOverImageSprite.setPosition(
            {float(windowWidth / 2 - gameOverImageSprite.getLocalBounds().width * k / 2), 30});
}

void GameOverActivity::start() {
    Injected<FieldController> f;
    f->resetGame();
    configureInjecting<FieldController>(1);
    activityManager->pop();
}

void GameOverActivity::exit() {
    window->close();
}

void GameOverActivity::handleState() {
    MenuActivity::handleState();
    restartButton.handleState();
    exitButton.handleState();
}


void GameOverActivity::handleEvent(sf::Event & event) {
    MenuActivity::handleEvent(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            activityManager->pop();
        }
    }
    restartButton.handleEvent(event);
    exitButton.handleEvent(event);
}

void GameOverActivity::draw(float time) {
    MenuActivity::draw(time);
    window->draw(gameOverImageSprite);

    restartButton.draw();
    exitButton.draw();
}


