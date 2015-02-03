#pragma once

//Includes
#include "mt.h"

#include <SFML/Graphics.hpp>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class Animation: public sf::Drawable
{
public:

	//Constructor & Destructor
	Animation();
	~Animation();

	//Access Methods
	
	//R&W
	sf::Sprite& getAnimatedSprite();
	//R-only
	sf::Vector2i getFrameSize() const;
	int getNumFrame() const;
	int getCurrentFrame() const;
	sf::Time getDuration() const;
	sf::Time getElapsedTime() const;
	bool getIsRepeat() const;
	bool getIsAnimated() const;

	//Modifying Methods
	void setAnimatedSprite(sf::Sprite animatedSprite);
	void setFrameSize(sf::Vector2i frameSize);
	void setNumFrame(int numFrame);
	void setCurrentFrame(int currentFrame);
	void setDuration(sf::Time duration);
	void setElapsedTime(sf::Time elapsedTime);
	void setIsRepeat(bool isRepeat);
	void setIsAnimated(bool isAnimated);
	
	//Functions
	void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void update(sf::Time dt) = 0;
	//Operator Overload

protected:

	//protected Functions

	//protected Attributes
	sf::Sprite animatedSprite_;
	//Dimensions of one frame
	sf::Vector2i frameSize_;
	//Number of frames in the animation
	int numFrame_;
	//Current frame the animation is displaying
	int currentFrame_;
	//Time to complete the animation
	sf::Time duration_;
	//Time elapsed since the beginning of the animation
	sf::Time elapsedTime_;
	//Bool dictates if the animation is to repeat itself when it finishes
	bool isRepeat_;
	//Bool dictates if the sprite is static or animated
	bool isAnimated_;

};
