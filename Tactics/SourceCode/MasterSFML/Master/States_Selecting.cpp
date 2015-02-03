//Includes
#include "States_Selecting.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
States_Selecting* States_Selecting::_instance = nullptr;

//Class Definition
States_Selecting::States_Selecting()
{
}

States_Selecting::~States_Selecting()
{
	_instance = nullptr;
}

void States_Selecting::erase()
{
	delete _instance;
}

//Singleton specific
States_Selecting* States_Selecting::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new States_Selecting();
	}
	return _instance;
}

//Access Method

//Modifying method

//Function
bool States_Selecting::handlePlayerInputSpecific(sf::Event::KeyEvent key, bool isPressed)
{
	switch (key.code)
	{
	case sf::Keyboard::Key::Return:
#if 1
		if (!isPressed)
		{
			Hex* currentHex = Selection::Instance()->getHex();
			if (!currentHex->isEmpty())
			{
				for (Entity* anyEntity: *currentHex->getEntities())
				{
					if (anyEntity->getCategory() & mt::Category::TypeCombo::AnyUnit)
					{
						Selection::Instance()->setSelectUnit(static_cast<Unit*>(anyEntity));

						Selection::Instance()->getCursor()->setColor(mt::Overlay::Color::Green);

						World::Instance()->makeOverlay(
							Selection::Instance()->getHex()->generateArea(
							GeneratorParameters(0,
							Selection::Instance()->getSelectUnit()->getUnitProperties(mt::Properties::movSpeed),
							0,
							false,
							0),
							mt::TypeArea::Circle),
							mt::Overlay::Blue);

						//somewhere here a pathfinding algorithm should
						//be considered to remove out of range hexes

						Command colorizeOverlay;
						colorizeOverlay.category = mt::Category::ColorFiltre;
						colorizeOverlay.action = colorizeOverlay.derivedAction<ColorFiltre>( 
							[] (ColorFiltre& filtre, sf::Time)
						{
							if(!Map::Instance()->getHex(filtre.getObjectCoordinates())->getEntities()->empty())
							{
								if (Selection::Instance()->getHex() != Map::Instance()->getHex(filtre.getObjectCoordinates()))
								{
									for(Entity* entity: *Map::Instance()->getHex(filtre.getObjectCoordinates())->getEntities())
									{
										if(typeid(*entity) == typeid(Unit))
										{
											filtre.setColor(mt::Overlay::Orange);
											return;
										}  
										if(typeid(*entity) == typeid(Object))
										{
											filtre.setColor(mt::Overlay::Red);
											return;
										}
									}
								}
								else
								{
									//filtre.setColor(mt::Overlay::Blue);
								}
							}
						});
						World::Instance()->getCommandQueue().push(colorizeOverlay);

						Player::Instance()->setState(States_UnitSelected::Instance());
						cout << "State: UnitSelected" << endl;
						break;
					}
				}
			}
		}
		return true;
#endif //Return(enter)

	case sf::Keyboard::Key::BackSpace: //fallthrough
	case sf::Keyboard::Key::Escape:
#if 1
		if (!isPressed)
		{
			//selection.setIsSelecting(false);
			Selection::Instance()->getCursor()->setColor(mt::Overlay::Color::Black);
			cout << "State: FreeCamera" << endl;
			Player::Instance()->setState(States_FreeCamera::Instance());
		}
		return true;
#endif //BackSpace

	case sf::Keyboard::A:
#if 1
		if (!isPressed && key.control)
		{
			unsigned int lenght = 8;
			unsigned int width = 3;
			unsigned int direction = 2;
			unsigned int firstDirection = 0;
			int typeArea = 0;
			bool isLarger = false;
			/****************************/
			cout << endl << "Lenght: ";
			cin >> lenght;
			cout << "Width: ";
			cin >> width;
			cout << "Direction: ";
			cin >> direction;
			cout << "FirstDiretion: ";
			cin >> firstDirection;
			cout << "typeArea[0,1]: ";
			cin >> typeArea;
			cout << "isLarger[0,1]: ";
			cin >> isLarger;
			if(cin.fail())
			throw runtime_error("Wrongful entry");
			//*/

			GeneratorParameters param = GeneratorParameters(lenght,width,direction,isLarger,firstDirection);
			vector<Hex*> area = 
				Selection::Instance()->getHex()->generateArea(param,(mt::TypeArea::TypeArea)mt::random(1));

			for(auto elem: area)
			{
				World::Instance()->createUnit(elem->getGridInfo().getPosColumn(),elem->getGridInfo().getPosRow());
			}
		}
		return true;
#endif //A
	}
	return false;
}

bool States_Selecting::handlePlayerInputArrows(sf::Event::KeyEvent key, bool isPressed)
{
	return States::handlePlayerInputArrows(key,isPressed);
}

void States_Selecting::handleRealtimeInputSpecific()
{
	//do nothing
}

//Operator Overload