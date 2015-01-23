#pragma once

//Includes
#include "Map.h"
#include "Hex.h"
#include "Filtre.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class ColorFiltre: public Filtre
{ 
public:
	//Constructor
	ColorFiltre();
	ColorFiltre(sf::Texture& texture, GridInfo pos = GridInfo());
	//Destructor
	~ColorFiltre();

	//R-only access

	//R-W access

	//Modifying method
	void setColor(mt::Overlay::Color color, mt::Overlay::Type type = mt::Overlay::Type::ColorFilter) override;

	//Function
	unsigned int getCategory() const override;

	//Operator Overload

private: 
	//Private Function

	//Private Attribute

}; 
