#pragma once

//Includes
#include "Animation.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class ObjectAnimation: public Animation
{
public:

	//Constructor & Destructor
	ObjectAnimation();
	~ObjectAnimation();
	//Access Methods
	
	//Modifying methods

	//Functions
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time dt) override;

	//Operator Overload

private:

	//Private Functions

	//Private Attributes

};
