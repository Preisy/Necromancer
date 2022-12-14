#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "Animation.hpp"


class AnimationManager
{

public:
    std::string currentAnim;
    std::map<std::string, Animation> animList;
    float x = 0;
    float y = 0;
    sf::Texture t;

    AnimationManager()
    {}

    ~AnimationManager()
    { animList.clear();
    }

    //загрузка из файла XML
    void loadFromXML(std::string fileName, std::string textureName) {
        if (!t.loadFromFile(textureName)) {
            throw std::runtime_error("cannot load from file");
        }

        TiXmlDocument animFile(fileName.c_str());

        animFile.LoadFile();

        TiXmlElement *head;
        head = animFile.FirstChildElement("sprites");

        TiXmlElement *animElement;
        animElement = head->FirstChildElement("animation");
        while(animElement)
        {
            Animation anim;
            currentAnim = animElement->Attribute("title");
            int delay = atoi(animElement->Attribute("delay"));
            anim.speed = 1.0/delay; anim.sprite.setTexture(t);

            TiXmlElement *cut;
            cut = animElement->FirstChildElement("cut");
            while (cut)
            {
                int x = atoi(cut->Attribute("x"));
                int y = atoi(cut->Attribute("y"));
                int w = atoi(cut->Attribute("w"));
                int h = atoi(cut->Attribute("h"));

                anim.frames.push_back( sf::IntRect(x,y,w,h) );
                anim.frames_flip.push_back( sf::IntRect(x+w,y,-w,h)  );
                cut = cut->NextSiblingElement("cut");
            }

            anim.sprite.setOrigin(0,anim.frames[0].height);

            animList[currentAnim] = anim;
            animElement = animElement->NextSiblingElement("animation");
        }
    }

    void set(std::string name)
    {
        currentAnim = name;
        animList[currentAnim].flip=0;
    }

    void setPosition(float x, float y) {
        this->x = x;
        this->y = y;
    }
    sf::Vector2f getPosition() {
        return {x, y};
    }

    void draw(sf::RenderWindow &window) {
        animList[currentAnim].sprite.setPosition(x,y);
        window.draw( animList[currentAnim].sprite );
    }

    void flip(bool b=1) {animList[currentAnim].flip = b;}

    void tick(float time){animList[currentAnim].tick(time);}

    void pause() {animList[currentAnim].isPlaying=false;}

    void play()  {animList[currentAnim].isPlaying=true;}

    void play(std::string name)  {animList[name].isPlaying=true;}

    bool isPlaying()  {return animList[currentAnim].isPlaying;}

    float getH()  {return animList[currentAnim].frames[0].height;}

    float getW() {return animList[currentAnim].frames[0].width;}

};