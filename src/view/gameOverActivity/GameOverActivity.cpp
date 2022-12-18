#include "GameOverActivity.h"

#include "controller/FieldController.h"


GameOverActivity::GameOverActivity()
        : restartButton("restart", [this]() { restart(); }, 300),
          exitButton("exit", [this]() { exit(); }, 400) {
    backgroundTexture.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\game_over_background.png)");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundMask.setFillColor(sf::Color(0x00000088));
    backgroundMask.setPosition(0, 0);
    backgroundMask.setSize({windowWidth, windowHeight});

    gameOverImageTexture.loadFromFile(R"(D:\C\3sem_cpp\Necromancer\resources\game_over_image.png)");
    gameOverImageSprite.setTexture(gameOverImageTexture);
    float k = float(0.5 * windowWidth) / (float) gameOverImageSprite.getTextureRect().width;
    gameOverImageSprite.setScale(k, k);

    gameOverImageSprite.setPosition(
            {float(windowWidth / 2 - gameOverImageSprite.getLocalBounds().width * k / 2), 30});

}

void GameOverActivity::restart() {
    Injected<FieldController> f;
    f->resetGame();
    configureInjecting<FieldController>(1);
    std::cout << "restart" << std::endl;
    activityManager->pop();
}

void GameOverActivity::exit() {
    window->close();
}

void GameOverActivity::handleState() {
    restartButton.handleState();
    exitButton.handleState();
}

void GameOverActivity::handleEvent(sf::Event & event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            activityManager->pop();
        }
    }
    restartButton.handleEvent(event);
    exitButton.handleEvent(event);
}

void GameOverActivity::update(float time) {}

void GameOverActivity::draw(float time) {
    window->draw(backgroundSprite);
    window->draw(backgroundMask);
    window->draw(gameOverImageSprite);

    restartButton.draw();
    exitButton.draw();
}