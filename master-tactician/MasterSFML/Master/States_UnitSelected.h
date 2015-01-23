#pragma once

//Includes
#include "States.h"
#include "States_FreeCamera.h"
#include "States_Selecting.h"
#include "States_UnitSelected.h"
#include "States_UnitSelected_GroundSelected.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class States_UnitSelected: public States
{ 
public:

	//Singleton specific
	static States_UnitSelected* Instance();
	void erase() override;

	//Destructor
	~States_UnitSelected();

	//R-only access

	//R-W access

	//Modifying method

	//Function
	bool handlePlayerInputSpecific(sf::Event::KeyEvent key, bool isPressed) override;
	bool handlePlayerInputArrows(sf::Event::KeyEvent key, bool isPressed) override;
	void handleRealtimeInputSpecific() override;

	//Operator Overload

protected: 
	States_UnitSelected();

private: 
	//Private Function

	//Private Attribute

	//Singleton specific
	static States_UnitSelected* _instance; 
}; 
