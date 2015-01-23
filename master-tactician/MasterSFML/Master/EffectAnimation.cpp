//Includes
#include "EffectAnimation.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
EffectAnimation::EffectAnimation()
{
}
EffectAnimation::~EffectAnimation()
{
}

//Access Methods

//Modifying methods

//Functions
void EffectAnimation::update(sf::Time dt)
{
	sf::Time frameDuration = duration_ / (float)numFrame_;
	elapsedTime_ += dt;
	sf::Vector2i textureBounds(animatedSprite_.getTexture()->getSize());
	sf::IntRect textureRect(animatedSprite_.getTextureRect());

	if (currentFrame_ == 0)
		textureRect = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);

	while (elapsedTime_ >= frameDuration && (currentFrame_ <= numFrame_ || isRepeat_))
	{
		textureRect.left += textureRect.width;
		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}
		elapsedTime_ -= frameDuration;
		if (isRepeat_)
		{
			currentFrame_ = (currentFrame_ + 1) % numFrame_;
			if (currentFrame_ == 0)
				textureRect = sf::IntRect(0, 0, frameSize_.x,
				frameSize_.y);
		}
		else
		{
			++currentFrame_;
		}
	}
	animatedSprite_.setTextureRect(textureRect);
}

//Operator Overloads
