#pragma once

#include "tinyxml.h"
#include <SFML/Graphics.hpp>



class Animation
{
public:
	std::vector<sf::IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool loop, flip, isPlaying;   // loop показвает зациклена ли анимация. Например анимация взрыва должна проиграться один раз и остановиться, loop=false
	sf::Sprite sprite;

	Animation()
	{
		currentFrame = 0;
		isPlaying=true;
		flip=false;
		loop=true;
	}

	void tick(float time, float speedK)
	{
		if (!isPlaying) return;

		currentFrame += speed * speedK * time;

		if (currentFrame > frames.size()) { currentFrame -= frames.size();
		                                    if (!loop) {isPlaying=false; return;}
		                                  }

		int i = currentFrame;
		sprite.setTextureRect( frames[i] );
		if (flip) sprite.setTextureRect( frames_flip[i] );
	}

};
