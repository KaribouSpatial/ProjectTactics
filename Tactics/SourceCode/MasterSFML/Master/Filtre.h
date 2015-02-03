#pragma once

//Includes
#include "Map.h"
#include "Hex.h"
#include "GridInfo.h"
#include "Unit.h"
#include "AnimatedFiltre.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class Filtre: public Entity, public AnimatedFiltre
{ 
public:
	//Destructor
	virtual ~Filtre() = 0;
	
	//R-only access
	const GridInfo getObjectCoordinates() const override;

	//R-W access
	sf::Sprite& getSprite() override;

	//Modifying method
	virtual void setColor(mt::Overlay::Color color, mt::Overlay::Type type = mt::Overlay::Type::ColorFilter) = 0;

	//Function
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateCurrent(sf::Time dt) override;
	unsigned int getCategory() const override = 0;

	//Operator Overload

private: 
	//update responsible of the animation
	void updateAnimation(sf::Time dt) override;

	//Private Function

	//Private Attribute

}; 
