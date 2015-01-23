#pragma once

//Includes
#include <SFML/Graphics.hpp>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class Animated
{
public:

	//Constructor

	//Destructor
	virtual ~Animated() = 0 {};

	//R-only access

	//R-W access
	
	//Modifying method

	//Function
	
	//Operator Overload

protected:

	//protected Function
	virtual void updateAnimation(sf::Time dt) = 0;

	//protected Attribute
	
};
