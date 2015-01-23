//Includes
#include "States_UnitSelected_GroundSelected.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
States_UnitSelected_GroundSelected* States_UnitSelected_GroundSelected::_instance = nullptr;

//Class Definition
States_UnitSelected_GroundSelected::States_UnitSelected_GroundSelected()
{
}

States_UnitSelected_GroundSelected::~States_UnitSelected_GroundSelected()
{
	_instance = nullptr;
}

void States_UnitSelected_GroundSelected::erase()
{
	delete _instance;
}

//Singleton specific
States_UnitSelected_GroundSelected* States_UnitSelected_GroundSelected::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new States_UnitSelected_GroundSelected();
	}
	return _instance;
}

//Access Method

//Modifying method

//Function
bool States_UnitSelected_GroundSelected::handlePlayerInputSpecific(sf::Event::KeyEvent key, bool isPressed)
{
	//do nothing
	return false;
}

bool States_UnitSelected_GroundSelected::handlePlayerInputArrows(sf::Event::KeyEvent key, bool isPressed)
{
	//do nothing
	return false;
}

void States_UnitSelected_GroundSelected::handleRealtimeInputSpecific()
{
	//do nothing
}

//Operator Overload