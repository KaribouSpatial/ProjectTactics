//Includes
#include "States_UnitSelected.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
States_UnitSelected* States_UnitSelected::_instance = nullptr;

//Class Definition
States_UnitSelected::States_UnitSelected()
{
}

States_UnitSelected::~States_UnitSelected()
{
	_instance = nullptr;
}

void States_UnitSelected::erase()
{
	delete _instance;
}

//Singleton specific
States_UnitSelected* States_UnitSelected::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new States_UnitSelected();
	}
	return _instance;
}

//Access Method

//Modifying method

//Function
bool States_UnitSelected::handlePlayerInputSpecific(sf::Event::KeyEvent key, bool isPressed)
{
	switch (key.code)
	{
	case sf::Keyboard::Key::Return:
#if 1
		if (!isPressed)
		{
			auto selectedUnitHex = Map::Instance()->getHex(Selection::Instance()->getSelectUnit()->getObjectCoordinates());
			if (Selection::Instance()->getHex()->calculateDistance(
				selectedUnitHex) > Selection::Instance()->getSelectUnit()->getUnitProperties(mt::Properties::movSpeed))
			{
				cout << "Out of Range" << endl;
				return true;
			}
			if (find_if(Selection::Instance()->getHex()->getEntities()->begin(),
				Selection::Instance()->getHex()->getEntities()->end(), [] (Entity* entity) ->bool
			{
				cout << typeid(*entity).name() << " " << typeid(Unit).name() << endl;
				if (typeid(*entity) == typeid(Unit) || typeid(*entity) == typeid(Object))
					return true;
				else
					return false;
			}) == Selection::Instance()->getHex()->getEntities()->end())
				//no object was found in the target hex, move the selection
			{
				Map::Instance()->modifyMapObject_move(*Selection::Instance()->getSelectUnit(),Selection::Instance()->getHex()->getGridInfo());
				World::Instance()->sortLayer(World::UnitL);

				sf::Vector2f pixelPosition = 
					mt::calculateObjectPixelPosition(
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(), 
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());

				Selection::Instance()->getSelectUnit()->getAnimation().getAnimatedSprite().setPosition(pixelPosition);
				Selection::Instance()->setSelectUnit(nullptr);

				Selection::Instance()->getCursor()->setColor(mt::Overlay::Color::White);
				Player::Instance()->setState(States_Selecting::Instance());
				cout << "State: Selecting" << endl;			
				//destroy the overlays
				World::Instance()->eraseLayer(World::Layer::OverlaysL);
			}
			else 
			{
				//an entity was found in the target hex
				//if the target is the same as the source
				for(auto element : *Selection::Instance()->getHex()->getEntities())
				{
					if (element == Selection::Instance()->getSelectUnit())
					{
						Selection::Instance()->setSelectUnit(nullptr);

						Selection::Instance()->getCursor()->setColor(mt::Overlay::Color::White);
						Player::Instance()->setState(States_Selecting::Instance());
						cout << "State: Selecting" << endl;
						//destroy the overlays
						World::Instance()->eraseLayer(World::Layer::OverlaysL);
						return true;
					}
				}
				//an entity was found in the target hex
				for(auto element : *Selection::Instance()->getHex()->getEntities())
				{
					Unit* unit = dynamic_cast<Unit*>(element);
					if (unit != nullptr)
					{
						Selection::Instance()->getHex()->calculateDistance(selectedUnitHex);
						Selection::Instance()->getSelectUnit()->dealDamageTo(unit);
						Selection::Instance()->getCursor()->setCoordinates(Selection::Instance()->getSelectUnit()->getObjectCoordinates());
						Selection::Instance()->setHex(selectedUnitHex;
						Selection::Instance()->setSelectUnit(nullptr);
						Selection::Instance()->getCursor()->setColor(mt::Overlay::Color::White);
						Player::Instance()->setState(States_Selecting::Instance());
						cout << "State: Selecting" << endl;
						//destroy the overlays
						World::Instance()->eraseLayer(World::Layer::OverlaysL);
						if(unit->getUnitProperties(mt::Properties::hp) <= 0)
						{
							//destroy the unit
							Map::Instance()->modifyMapObject_delete(*unit);
							unit->suicide();
						}
						return true;
					}
					
				}
				//play an error sound or show an error message
				cout << "Target hex is occupied" << endl;
			}
		}
		return true;
#endif //Return(enter)

	case sf::Keyboard::Key::BackSpace: //fallthrough
	case sf::Keyboard::Key::Escape:
#if 1
		if (!isPressed)
		{
			Selection::Instance()->setSelectUnit(nullptr);
			Selection::Instance()->getCursor()->setColor(mt::Overlay::Color::White);

			cout << "State: Selecting" << endl;
			Player::Instance()->setState(States_Selecting::Instance());
			//destroy the overlays
			World::Instance()->eraseLayer(World::Layer::OverlaysL);
		}
		return true;
#endif //BackSpace
	}
	return false;
}

bool States_UnitSelected::handlePlayerInputArrows(sf::Event::KeyEvent key, bool isPressed)
{
	/*Command colorizeSelection;
	colorizeSelection.category = mt::Category::Selection;
	colorizeSelection.action = colorizeSelection.derivedAction<SelectionFiltre>
		([] (SelectionFiltre& filtre, sf::Time)
	{
		//if hex is occupied and not a unit
		/*if(!Map::Instance()->getHex(filtre.getObjectCoordinates())->getEntities()->empty() &&
			Map::Instance()->getHex(filtre.getObjectCoordinates()) !=
			selectedUnitHex
		{
			filtre.setColor(mt::Overlay::Red);
		}
		else
		{
			filtre.setColor(mt::Overlay::Contour);
		}
	});*/

	switch (key.code)
	{
	case sf::Keyboard::Key::Left:
#if 1
		if (isPressed)
		{
			Hex* currentHex = Selection::Instance()->getHex()->getAdjacentHex(mt::Direction::LEFT);
			if (currentHex != nullptr /*&& !currentHex->isBorder()*/
				&& Map::Instance()->getHex(Selection::Instance()->getSelectUnit()->getObjectCoordinates())->calculateDistance(currentHex) 
				<= Selection::Instance()->getSelectUnit()->getUnitProperties(mt::Properties::movSpeed))
			{
				Selection::Instance()->getCursor()->setCoordinates(currentHex->getGridInfo());
				Selection::Instance()->setHex(currentHex);
				//cout << "Pos: (" << currentHex->getGridInfo().getPosColumn() << ", " << currentHex->getGridInfo().getPosRow() << ")"<< endl;
				//pair de float selon la position en pixel de la case
				auto vect = mt::calculatePixelPosition(
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(),
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());
				//si la position en pixel de la case est a l'exterieur de l'ecran, on bouge l'ecran
				if (vect.x < MyView::Instance()->getCenter().x-MyView::Instance()->getSize().x/2)
				{
					//une case est 128/64en faisant +/- 256, on bouge la camera de deux cases
					MyView::Instance()->move(-256,0);
					MyView::Instance()->check();
				}
			}
		}
		//World::Instance()->getCommandQueue().push(colorizeSelection);
		return true;  
#endif //Left
	case sf::Keyboard::Key::Right:
#if 1
		if (isPressed)
		{
			Hex* currentHex = Selection::Instance()->getHex()->getAdjacentHex(mt::Direction::RIGHT);
			if (currentHex != nullptr /*&& !currentHex->isBorder()*/
				&& Map::Instance()->getHex(Selection::Instance()->getSelectUnit()->getObjectCoordinates())->calculateDistance(currentHex)
				<= Selection::Instance()->getSelectUnit()->getUnitProperties(mt::Properties::movSpeed))
			{
				Selection::Instance()->getCursor()->setCoordinates(currentHex->getGridInfo());
				Selection::Instance()->setHex(currentHex);
				//cout << "Pos: (" << currentHex->getGridInfo().getPosColumn() << ", " << currentHex->getGridInfo().getPosRow() << ")"<< endl;
				//pair de float selon la position en pixel de la case
				auto vect = mt::calculatePixelPosition(
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(),
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());
				if (vect.x+129 > MyView::Instance()->getCenter().x+MyView::Instance()->getSize().x/2)
				{
					MyView::Instance()->move(256,0);
					MyView::Instance()->check();
				}
			}
		}
		//World::Instance()->getCommandQueue().push(colorizeSelection);
		return true;
#endif //Right
	case sf::Keyboard::Key::Up:
#if 1
		if (isPressed)
		{
			//Complicated BS to select the right Hex upward
			Hex* currentHex = Selection::Instance()->getHex()->getAdjacentHex(
				5*(!(Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow()&1)));
			if (currentHex != nullptr /*&& !currentHex->isBorder()*/
				&& Map::Instance()->getHex(Selection::Instance()->getSelectUnit()->getObjectCoordinates())->calculateDistance(currentHex)
				<= Selection::Instance()->getSelectUnit()->getUnitProperties(mt::Properties::movSpeed))
			{
				Selection::Instance()->getCursor()->setCoordinates(currentHex->getGridInfo());
				Selection::Instance()->setHex(currentHex);
				//cout << "Pos: (" << currentHex->getGridInfo().getPosColumn() << ", " << currentHex->getGridInfo().getPosRow() << ")"<< endl;
				//pair de float selon la position en pixel de la case
				auto vect = mt::calculatePixelPosition(
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(),
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());
				if (vect.y < MyView::Instance()->getCenter().y-MyView::Instance()->getSize().y/2)
				{
					MyView::Instance()->move(0,-128);
					MyView::Instance()->check();
				}
			}
		}
		//World::Instance()->getCommandQueue().push(colorizeSelection);
		return true;
#endif //Up
	case sf::Keyboard::Key::Down:
#if 1
		if (isPressed)
		{
			Hex* currentHex = Selection::Instance()->getHex()->getAdjacentHex(
				mt::Direction::BOT_RIGHT+(!(Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow()&1)));
			if (currentHex != nullptr /*&& !currentHex->isBorder()*/
				&& Map::Instance()->getHex(Selection::Instance()->getSelectUnit()->getObjectCoordinates())->calculateDistance(currentHex)
				<= Selection::Instance()->getSelectUnit()->getUnitProperties(mt::Properties::movSpeed))
			{
				Selection::Instance()->getCursor()->setCoordinates(currentHex->getGridInfo());
				Selection::Instance()->setHex(currentHex);
				//cout << "Pos: (" << currentHex->getGridInfo().getPosColumn() << ", " << currentHex->getGridInfo().getPosRow() << ")"<< endl;
				//pair de float selon la position en pixel de la case
				auto vect = mt::calculatePixelPosition(
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(),
					Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());
				if (vect.y+65 > MyView::Instance()->getCenter().y+MyView::Instance()->getSize().y/2)
				{
					MyView::Instance()->move(0,128);
					MyView::Instance()->check();
				}
			}
		}
		//World::Instance()->getCommandQueue().push(colorizeSelection);
		return true;  
#endif //Down
	}
	return false;
}

void States_UnitSelected::handleRealtimeInputSpecific()
{
	//do nothing
}

//Operator Overload