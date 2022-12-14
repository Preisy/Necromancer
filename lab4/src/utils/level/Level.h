#pragma once

#include "Object.h"
#include "Layer.h"

class Level//главный класс - уровень
{
public:
    bool LoadFromFile(std::string filename);//возвращает false если не получилось загрузить
    Object GetObject(std::string name) const;

    std::vector<Object> GetObjects(std::string name) const;//выдаем объект в наш уровень
    std::vector<Object> GetAllObjects();//выдаем все объекты в наш уровень
    void Draw(sf::RenderWindow & window) const;//рисуем в окно
    sf::Vector2i GetTileSize();//получаем размер тайла
private:
    int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
    int firstTileID;//получаем айди первого тайла
    sf::Rect<float> drawingBounds;//размер части карты которую рисуем
    sf::Texture tilesetImage;//текстура карты
    std::vector<Object> objects;//массив типа Объекты, который мы создали
    std::vector<Layer> layers;
public:
    std::vector<Object> & getObjects();

    int getTileWidth() const;

    int getTileHeight() const;

    sf::Vector2<unsigned int> getLevelSize() const;

public:
    std::vector<Layer> & getLayers();
};
