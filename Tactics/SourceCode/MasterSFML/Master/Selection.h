#pragma once

//Includes
#include "Map.h"
#include "Hex.h"
#include "GridInfo.h"
#include "Unit.h"
#include "SelectionFiltre.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class Selection
{
public:
	//Singleton specific
	static Selection* Instance();
	static void create(sf::Texture& texture);
	void erase();

	//Destructor
	~Selection();

	//Access Method
	//R-only access
	Hex* getHex() const;

	//R-W Access
	Unit* getSelectUnit();
	SelectionFiltre* getCursor();
	sf::Sprite& getSprite();

	//Modifying methods
	void setHex(Hex* hex);
	void setSelectUnit(Unit* selectUnit);

	//Functions

	//Operator Overload

protected: 
	//Constructor
	Selection();
	Selection(sf::Texture& texture);

private:

	//Private Functions

	//Private Attributes
	SelectionFiltre* selectionFiltre_;
	Hex* selectHex_;
	Unit* selectUnit_;

	//Singleton specific
	static Selection* _instance;
};
