#include "MainMenuActivity.h"

#include "controller/FieldController.h"

MainMenuActivity::MainMenuActivity()
        : startButton("Restart    ", [this]() { restart(); }, 300),
          exitButton("Exit", [this]() { exit(); }, 400) {
    gameOverImageTexture.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\game_over_image.png)");
    gameOverImageSprite.setTexture(gameOverImageTexture);
    float k = float(0.5 * windowWidth) / (float) gameOverImageSprite.getTextureRect().width;
    gameOverImageSprite.setScale(k, k);

    gameOverImageSprite.setPosition(
            {float(windowWidth / 2 - gameOverImageSprite.getLocalBounds().width * k / 2), 30});
}

void MainMenuActivity::restart() {
    Injected<FieldController> f;
    f->resetGame();
    configureInjecting<FieldController>(1);
    activityManager->pop();
}

void MainMenuActivity::exit() {
   window->close();
}

void MainMenuActivity::handleState() {
    MenuActivity::handleState();
    startButton.handleState();
    exitButton.handleState();
}


void MainMenuActivity::handleEvent(sf::Event & event) {
    MenuActivity::handleEvent(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            activityManager->pop();
        }
    }
    startButton.handleEvent(event);
    exitButton.handleEvent(event);
}

void MainMenuActivity::draw(float time) {
    MenuActivity::draw(time);
    window->draw(gameOverImageSprite);

    startButton.draw();
    exitButton.draw();
}


