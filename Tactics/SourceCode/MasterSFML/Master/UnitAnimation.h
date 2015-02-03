#pragma once

//Includes
#include "Animation.h"

#include <assert.h>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class UnitAnimation: public Animation
{
public:

	//Constructor & Destructor
	UnitAnimation();
	~UnitAnimation();
	//Access Methods
	
	//Modifying methods
	void setDirection(mt::Direction::Direction direction);

	//Functions
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Time dt) override;
	//Operator Overload

private:

	//Private Functions

	//Private Attributes
	int direction_;
};
