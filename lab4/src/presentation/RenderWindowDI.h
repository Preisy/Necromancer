#pragma once

#include <SFML/Graphics.hpp>
#include "utils/DependencyInjection.h"
#include "config.h"

injectAsSingleton(sf::RenderWindow, sf::VideoMode(1000, 20 * fieldCellSize), "Necromancer")

