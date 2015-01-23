#pragma once

//Includes
#include "CommandQueue.h"
#include "Command.h"
#include "World.h"
#include "States.h"

#include <SFML/Graphics.hpp>
#include <iostream>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes
class States;

//Class Declaration
class Player
{
public:
	//Singleton specific
	static Player* Instance();
	void erase();

	//Destructor
	~Player();

	//R-only access
	const States* getState() const;
	//R-W access
	
	//Modifying method
	void setState(States* state);

	//Function
	void handleEvent(const sf::Event& event);

	void handleRealtimeInput();
	//Operator Overload

protected: 
	//Constructor
	Player();

private:

	//Private Function
	//Specific Event Handling Logic, isPressed is true on KeyPress 
	//and false on KeyRelease. Transfers request to _state
	void handlePlayerInput(sf::Event::KeyEvent key, bool isPressed);

	//Private Attribute
	States* state_;

	//Singleton specific
	static Player* _instance; 
};
