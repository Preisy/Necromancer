#pragma once

#include <SFML/Graphics.hpp>
#include "RenderWindowDI.h"
#include "config.h"

class HealthBarView {
    Injected<sf::RenderWindow> window;
    sf::RectangleShape healthWrapper;
    sf::RectangleShape health;
    sf::RectangleShape manaWrapper;
    sf::RectangleShape mana;
    float maxBarsSize = 200;
    float barsHeight = 6;

public:
    HealthBarView() {
        healthWrapper.setSize({maxBarsSize, barsHeight});
        healthWrapper.setFillColor(sf::Color(0x626262bf));
        healthWrapper.setOutlineColor(sf::Color(0x010101bf));
        healthWrapper.setOutlineThickness(2.3);
        healthWrapper.setPosition(20, windowHeight - 10*4);

        health.setFillColor(sf::Color(0xe51e1ebf));
        health.setPosition(20, windowHeight - 10*4);


        manaWrapper.setSize({maxBarsSize, barsHeight});
        manaWrapper.setFillColor(sf::Color(0x626262bf));
        manaWrapper.setOutlineColor(sf::Color(0x010101bf));
        manaWrapper.setOutlineThickness(2.3);
        manaWrapper.setPosition(20, windowHeight - 10*2);

        mana.setFillColor(sf::Color(0x281ee5bf));
        mana.setPosition(20, windowHeight - 10*2);

    }

    void draw(const std::shared_ptr<PlayerModel> & playerModel, float time) {
        float kHealth = playerModel->getHealth() / playerModel->getMaxHealth();
        if (kHealth < 0) kHealth = 0;
        float healthWidth = maxBarsSize * kHealth;
        health.setSize({healthWidth, barsHeight});

        float kMana = playerModel->getMana() / playerModel->getMaxMana();
        if (kMana < 0) kMana = 0;
        float manaWidth = maxBarsSize * kMana;
        mana.setSize({manaWidth, barsHeight});

        window->draw(healthWrapper);
        window->draw(health);
        window->draw(manaWrapper);
        window->draw(mana);
    }
};