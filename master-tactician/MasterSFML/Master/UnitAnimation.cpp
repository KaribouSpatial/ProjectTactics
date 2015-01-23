//Includes
#include "UnitAnimation.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
UnitAnimation::UnitAnimation()
{
}
UnitAnimation::~UnitAnimation()
{
}

//Access Methods

//Modifying methods
void UnitAnimation::setDirection(mt::Direction::Direction direction)
{
	direction_ = direction;
}

//Functions
void UnitAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(animatedSprite_, states);
}

void UnitAnimation::update(sf::Time dt)
{
	int directionToSpriteCoord = 0;

	switch (direction_)
	{
	case 0:
		//fallthrough
	case 5:
		directionToSpriteCoord = 96;
		break;
	case 1:
		directionToSpriteCoord = 64;
		break;
	case 2:
		//fallthrough
	case 3:
		directionToSpriteCoord = 0;
		break;
	case 4:
		directionToSpriteCoord = 32;
		break;
	default:
		assert(1==0);
		break;
	}
	sf::IntRect textureRect(animatedSprite_.getTextureRect());
	
	if (isAnimated_)
	{
		sf::Time frameDuration = duration_ / (float)numFrame_;
		elapsedTime_ += dt;

		while (elapsedTime_ >= frameDuration)
		{
			switch (currentFrame_)
			{
			case 0:
				textureRect = sf::IntRect(0, directionToSpriteCoord, frameSize_.x, frameSize_.y);
				break;
			case 1:
				//fallthrough
			case 2:
				textureRect.left += textureRect.width;
				break;
			case 3:
				textureRect.left -= textureRect.width;
				break;
			}
			++currentFrame_;
			if (currentFrame_ > 3)
				currentFrame_ = 0;
			elapsedTime_ -= frameDuration;
		}
		animatedSprite_.setTextureRect(textureRect); 
	}
}
//Operator Overloads
