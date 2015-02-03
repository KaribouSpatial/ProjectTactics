#pragma once

//Includes
#include "Command.h"
#include "Selection.h"
#include "World.h"
#include "Player.h"

#include <iostream>

#include <SFML/Graphics.hpp>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes
class Player;

//Class Declaration
class States
{
public:
	//Destructor
	virtual ~States() = 0;
	virtual void erase() = 0;
	//R-only access

	//R-W access

	//Modifying method

	//Function
	void handlePlayerInputTemplate(sf::Event::KeyEvent key, bool isPressed);
public:
	void handleRealtimeInputTemplate();

	//Operator Overload

protected:
	//Template Method Pattern Function
	virtual bool handlePlayerInputSpecific(sf::Event::KeyEvent key, bool isPressed) = 0;
	//Template Method Pattern Function
	virtual bool handlePlayerInputArrows(sf::Event::KeyEvent key, bool isPressed) = 0;
	//Template Method Patten Function
	virtual void handleRealtimeInputSpecific() = 0;

private:

	//Private Function

	//Private Attribute

};
