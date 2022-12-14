#pragma once

#include <SFML/Graphics.hpp>

struct Layer //слои
{
    int opacity;//непрозрачность слоя
    std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
    std::vector<sf::Sprite> & getTiles();
};
