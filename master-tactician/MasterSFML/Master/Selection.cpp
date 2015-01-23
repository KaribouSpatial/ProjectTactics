//Includes
#include "Selection.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
Selection* Selection::_instance = nullptr;

//Class Definition
//Constructor & Destructor
Selection::Selection()
{
}

Selection::Selection(sf::Texture& texture):
	selectUnit_(nullptr),
	selectionFiltre_(new SelectionFiltre(texture))
{
	selectionFiltre_->setColor(mt::Overlay::White);
	selectionFiltre_->setID(0);

	selectHex_ = Map::Instance()->getHex(selectionFiltre_->getObjectCoordinates());
}

Selection::~Selection()
{
	cout << "~" << typeid(*this).name() << endl;
	_instance = nullptr;
	selectHex_ = nullptr;
	selectUnit_ = nullptr;
}

void Selection::create(sf::Texture& texture)
{
	_instance = new Selection(texture);
}


void Selection::erase()
{
	delete _instance;
}

Selection* Selection::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new Selection();
	}
	return _instance;
}

//Access Methods
Hex* Selection::getHex() const
{
	return selectHex_;
}

Unit* Selection::getSelectUnit()
{
	return selectUnit_;
}

SelectionFiltre* Selection::getCursor()
{
	return selectionFiltre_;
}

sf::Sprite& Selection::getSprite()
{
	return selectionFiltre_->getSprite();
}

//Modifying methods
void Selection::setHex(Hex* hex)
{
	selectHex_ = hex;
}

void Selection::setSelectUnit(Unit* selectUnit)
{
	selectUnit_ = selectUnit;
}

//Functions

//Operator Overloads
