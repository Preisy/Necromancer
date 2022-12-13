#pragma once

#include <SFML/Graphics.hpp>
#include "utils/DependencyInjection.h"
#include "config.h"

injectAsSingleton(sf::RenderWindow, sf::VideoMode(windowWidth, windowHeight), "Necromancer")
//injectAsSingleton(sf::RenderWindow, sf::VideoMode(30*fieldCellSize, 25*fieldCellSize), "Necromancer")

