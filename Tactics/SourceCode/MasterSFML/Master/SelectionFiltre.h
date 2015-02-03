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
class SelectionFiltre: public Filtre
{ 
public:
	//Constructor
	SelectionFiltre();
	SelectionFiltre(sf::Texture& texture, GridInfo pos = GridInfo());
	//Destructor
	~SelectionFiltre();

	//R-only access

	//R-W access

	//Modifying method
	void setColor(mt::Overlay::Color color, mt::Overlay::Type type = mt::Overlay::Type::Selection) override;

	//Function
	unsigned int getCategory() const override;

	//Operator Overload

private: 
	//Private Function

	//Private Attribute

}; 
