#pragma once


struct Layer //слои
{
    int opacity;//непрозрачность слоя
    std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
    std::vector<sf::Sprite> & getTiles();
};

std::vector<sf::Sprite> & Layer::getTiles() {
    return tiles;
}
