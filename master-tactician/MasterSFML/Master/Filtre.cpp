//Includes
#include "Filtre.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Destructor
Filtre::~Filtre() 
{
}

//Access Method
const GridInfo Filtre::getObjectCoordinates() const
{
	return Entity::getObjectCoordinates();
}

sf::Sprite& Filtre::getSprite()
{
	return animation_.getAnimatedSprite();
}

//Modifying method

//Function
void Filtre::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(animation_, states);
}

void Filtre::updateCurrent(sf::Time dt)
{
	animation_.getAnimatedSprite().setPosition(mt::calculatePixelPosition(getObjectCoordinates().getPosColumn(),getObjectCoordinates().getPosRow()));
	updateAnimation(dt);
}

unsigned int Filtre::getCategory() const
{
	return mt::Category::ColorFiltre;
}

void Filtre::updateAnimation(sf::Time dt)
{
	animation_.update(dt);
}

//Operator Overload