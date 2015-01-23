#pragma once

//Includes
#include "ObjectAnimation.h"
#include "Entity.h"
#include "AnimatedObject.h"

#include <vector>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class Object : public Entity, public AnimatedObject
{
public:

	//Constructor & Destructor
	Object();
	Object(mt::texPair& texture, mt::BinPathingStruct pathing = mt::stdGround,
		GridInfo startPos = GridInfo(0,0));
	Object(Object& object);
	~Object();

	//Access Method
	//R-W access
	sf::Sprite& getSprite() override;

	//Modifying method

	//Function
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateCurrent(sf::Time dt) override;
	
	unsigned int getCategory() const override;

private:

	//private function
	void updateAnimation(sf::Time dt) override;

	//private attribute
	
};
