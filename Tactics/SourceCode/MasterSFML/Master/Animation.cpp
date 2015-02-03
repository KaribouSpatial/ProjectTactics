//Includes
#include "Animation.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
Animation::Animation()
{
	currentFrame_ = 0;
}
Animation::~Animation()
{

}

//Access Methods
sf::Sprite& Animation::getAnimatedSprite()
{
	return animatedSprite_;
}

sf::Vector2i Animation::getFrameSize() const
{
	return frameSize_;
}

int Animation::getNumFrame() const
{
	return numFrame_;
}

int Animation::getCurrentFrame() const
{
	return currentFrame_;
}

sf::Time Animation::getDuration() const
{
	return duration_;
}

sf::Time Animation::getElapsedTime() const
{
	return elapsedTime_;
}

bool Animation::getIsRepeat() const
{
	return isRepeat_;
}

bool Animation::getIsAnimated() const
{
	return isAnimated_;
}

//Modifying Methods
void Animation::setAnimatedSprite(sf::Sprite animatedSprite)
{
	animatedSprite_ = animatedSprite;
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
	frameSize_ = frameSize;
}

void Animation::setNumFrame(int numFrame)
{
	numFrame_ = numFrame;
}

void Animation::setCurrentFrame(int currentFrame)
{
	currentFrame_ = currentFrame;
}

void Animation::setDuration(sf::Time duration)
{
	duration_ = duration;
}

void Animation::setElapsedTime(sf::Time elapsedTime)
{
	elapsedTime_ = elapsedTime;
}

void Animation::setIsRepeat(bool isRepeat)
{
	isRepeat_ = isRepeat;
}

void Animation::setIsAnimated(bool isAnimated)
{
	isAnimated_ = isAnimated;
}
//Functions


//Operator Overloads
