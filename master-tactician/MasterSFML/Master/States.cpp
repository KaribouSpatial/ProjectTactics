//Includes
#include "States.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
States::~States()
{
}

//Access Method

//Modifying method

//Function
void States::handlePlayerInputTemplate(sf::Event::KeyEvent key, bool isPressed)
{
	switch (key.code)
	{
#if 1
	case sf::Keyboard::Key::Unknown:
		return;
	case sf::Keyboard::Key::B:
		return;
	case sf::Keyboard::Key::C:
		return;
	case sf::Keyboard::Key::D:
		return;
	case sf::Keyboard::Key::E:
		return;
	case sf::Keyboard::Key::F:
		return;
	case sf::Keyboard::Key::G:
		return;
	case sf::Keyboard::Key::H:
		return;
	case sf::Keyboard::Key::I:
		return;
	case sf::Keyboard::Key::J:
		return;
	case sf::Keyboard::Key::K:
		return;
	case sf::Keyboard::Key::L:
		return;
	case sf::Keyboard::Key::M:
		return;
	case sf::Keyboard::Key::N:
		return;
	case sf::Keyboard::Key::O:
		return;
	case sf::Keyboard::Key::P:
		return;
	case sf::Keyboard::Key::Q:
		return;
#endif

	case sf::Keyboard::Key::R:
		//ALT-R used in game
#if 1
		if (isPressed)
		{
			Hex* currentHex = Map::Instance()->getHex(Selection::Instance()->getCursor()->getObjectCoordinates());
			auto listEntity = *currentHex->getEntities();
			if (!listEntity.empty())
			{
				for(auto entity : listEntity)
				{
					if(entity->getCategory() || mt::Category::AnyUnit)
					{
						Unit* tempUnit = static_cast<Unit*>(entity);
						short direction = tempUnit->getUnitProperties(mt::Properties::Facing);
						if (direction == 5)
							direction = 0;
						else
							++direction;
						tempUnit->setUnitProperties(mt::Properties::Facing, direction);
						cout << "Rotating " << tempUnit->getName() << endl;
						break;
					}
				}
			}
		}
		return;
#endif //R

#if 1
	case sf::Keyboard::Key::S:
		return;
	case sf::Keyboard::Key::T:
		return;
	case sf::Keyboard::Key::U:
		//CTRL-U used in game
		return;
	case sf::Keyboard::Key::V:
		return;
	case sf::Keyboard::Key::W:
		return;
	case sf::Keyboard::Key::X:
		return;
	case sf::Keyboard::Key::Y:
		return;
	case sf::Keyboard::Key::Z:
		return;
	case sf::Keyboard::Key::Num0:
		return;
	case sf::Keyboard::Key::Num1:
		return;
	case sf::Keyboard::Key::Num2:
		return;
	case sf::Keyboard::Key::Num3:
		return;
	case sf::Keyboard::Key::Num4:
		return;
	case sf::Keyboard::Key::Num5:
		return;
	case sf::Keyboard::Key::Num6:
		return;
	case sf::Keyboard::Key::Num7:
		return;
	case sf::Keyboard::Key::Num8:
		return;
	case sf::Keyboard::Key::Num9:
		return;
	case sf::Keyboard::Key::LControl:
		return;
	case sf::Keyboard::Key::LShift:
		return;
	case sf::Keyboard::Key::LAlt:
		return;
	case sf::Keyboard::Key::LSystem:
		return;
	case sf::Keyboard::Key::RControl:
		return;
	case sf::Keyboard::Key::RShift:
		return;
	case sf::Keyboard::Key::RAlt:
		return;
	case sf::Keyboard::Key::RSystem:
		return;
	case sf::Keyboard::Key::Menu:
		return;
	case sf::Keyboard::Key::LBracket:
		return;
	case sf::Keyboard::Key::RBracket:
		//used in game
		return;
	case sf::Keyboard::Key::SemiColon:
		return;
	case sf::Keyboard::Key::Comma:
		return;
	case sf::Keyboard::Key::Period:
		return;
	case sf::Keyboard::Key::Quote:
		return;
	case sf::Keyboard::Key::Slash:
		return;
	case sf::Keyboard::Key::BackSlash:
		//used in game
		return;
	case sf::Keyboard::Key::Tilde:
		return;
	case sf::Keyboard::Key::Equal:
		return;
	case sf::Keyboard::Key::Dash:
		return;
	case sf::Keyboard::Key::Space:
		return;
	case sf::Keyboard::Key::Tab:
		return;
	case sf::Keyboard::Key::PageUp:
		return;
	case sf::Keyboard::Key::PageDown:
		return;
	case sf::Keyboard::Key::End:
		return;
	case sf::Keyboard::Key::Home:
		return;
	case sf::Keyboard::Key::Insert:
		return;
	case sf::Keyboard::Key::Delete:
		return;
#endif

	case sf::Keyboard::Key::Add:
#if 1
		if (isPressed)
		{
			cout << "Adding a unit to the map" << endl;
			World::Instance()->createUnit();
		}
		return;   
#endif //Add
	case sf::Keyboard::Key::Subtract:
#if 1
		if (!isPressed)
		{
			cout << "How many adds?" << endl;
			int answer;
			cin >> answer;
			for (int i = 0; i < answer; ++i)
			{
				World::Instance()->createUnit();
			}
		}
		return;  
#endif //Substract

#if 1
	case sf::Keyboard::Key::Multiply:
		return;
	case sf::Keyboard::Key::Divide:
		return;
	case sf::Keyboard::Key::Numpad0:
		return;
	case sf::Keyboard::Key::Numpad1:
		return;
	case sf::Keyboard::Key::Numpad2:
		return;
	case sf::Keyboard::Key::Numpad3:
		return;
	case sf::Keyboard::Key::Numpad4:
		return;
	case sf::Keyboard::Key::Numpad5:
		return;
	case sf::Keyboard::Key::Numpad6:
		return;
	case sf::Keyboard::Key::Numpad7:
		return;
	case sf::Keyboard::Key::Numpad8:
		return;
	case sf::Keyboard::Key::Numpad9:
		return;
	case sf::Keyboard::Key::F1:
		return;
	case sf::Keyboard::Key::F2:
		return;
	case sf::Keyboard::Key::F3:
		return;
	case sf::Keyboard::Key::F4:
		//alt-f4 used in game
		return;
	case sf::Keyboard::Key::F5:
		return;
	case sf::Keyboard::Key::F6:
		return;
	case sf::Keyboard::Key::F7:
		return;
	case sf::Keyboard::Key::F8:
		return;
	case sf::Keyboard::Key::F9:
		return;
	case sf::Keyboard::Key::F10:
		return;
	case sf::Keyboard::Key::F11:
		return;
	case sf::Keyboard::Key::F12:
		return;
	case sf::Keyboard::Key::F13:
		return;
	case sf::Keyboard::Key::F14:
		return;
	case sf::Keyboard::Key::F15:
		return;
	case sf::Keyboard::Key::Pause:
		return;
	case sf::Keyboard::Key::KeyCount:
		return;
#endif  
	}

	if(handlePlayerInputSpecific(key,isPressed))
		return;
	if(handlePlayerInputArrows(key,isPressed))
		return;
}

/*bool States::handlePlayerInputSpecific(sf::Event::KeyEvent key, bool isPressed)
{
throw runtime_error("Error in: States::handlePlayerInputSpecific");
}*/

bool States::handlePlayerInputArrows(sf::Event::KeyEvent key, bool isPressed)
{
	switch (key.code)
	{
	case sf::Keyboard::Key::Left:
#if 1
		if (isPressed)
		{
			Hex* currentHex = Selection::Instance()->getHex()->getAdjacentHex(mt::Direction::LEFT);
			if (currentHex != nullptr /*&& !currentHex->isBorder()*/)
			{
				Selection::Instance()->getCursor()->setCoordinates(currentHex->getGridInfo());
				Selection::Instance()->setHex(currentHex);
				//cout << "Pos: (" << currentHex->getGridInfo().getPosColumn() << ", " << currentHex->getGridInfo().getPosRow() << ")"<< endl;
				//pair de float selon la position en pixel de la case
				auto vect = mt::calculatePixelPosition(Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(), Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());
				//si la position en pixel de la case est a l'exterieur de l'ecran, on bouge l'ecran
				if (vect.x < MyView::Instance()->getCenter().x-MyView::Instance()->getSize().x/2)
				{
					//une case est 128/64en faisant +/- 256, on bouge la camera de deux cases
					MyView::Instance()->move(-256,0);
					MyView::Instance()->check();
				}
			}
		}
		return true;  
#endif //Left
	case sf::Keyboard::Key::Right:
#if 1
		if (isPressed)
		{
			Hex* currentHex = Selection::Instance()->getHex()->getAdjacentHex(mt::Direction::RIGHT);
			if (currentHex != nullptr /*&& !currentHex->isBorder()*/)
			{
				Selection::Instance()->getCursor()->setCoordinates(currentHex->getGridInfo());
				Selection::Instance()->setHex(currentHex);
				//cout << "Pos: (" << currentHex->getGridInfo().getPosColumn() << ", " << currentHex->getGridInfo().getPosRow() << ")"<< endl;
				//pair de float selon la position en pixel de la case
				auto vect = mt::calculatePixelPosition(Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(), Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());
				if (vect.x+129 > MyView::Instance()->getCenter().x+MyView::Instance()->getSize().x/2)
				{
					MyView::Instance()->move(256,0);
					MyView::Instance()->check();
				}
			}
		}
		return true;
#endif //Right
	case sf::Keyboard::Key::Up:
#if 1
		if (isPressed)
		{
			//Complicated BS to select the right Hex upward
			Hex* currentHex = Selection::Instance()->getHex()->getAdjacentHex(
				5*(!(Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow()&1)));
			if (currentHex != nullptr /*&& !currentHex->isBorder()*/)
			{
				Selection::Instance()->getCursor()->setCoordinates(currentHex->getGridInfo());
				Selection::Instance()->setHex(currentHex);
				//cout << "Pos: (" << currentHex->getGridInfo().getPosColumn() << ", " << currentHex->getGridInfo().getPosRow() << ")"<< endl;
				//pair de float selon la position en pixel de la case
				auto vect = mt::calculatePixelPosition(Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(), Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());
				if (vect.y < MyView::Instance()->getCenter().y-MyView::Instance()->getSize().y/2)
				{
					MyView::Instance()->move(0,-128);
					MyView::Instance()->check();
				}
			}
		}
		return true;
#endif //Up
	case sf::Keyboard::Key::Down:
#if 1
		if (isPressed)
		{
			Hex* currentHex = Selection::Instance()->getHex()->getAdjacentHex(
				mt::Direction::BOT_RIGHT+(!(Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow()&1)));
			if (currentHex != nullptr /*&& !currentHex->isBorder()*/)
			{
				Selection::Instance()->getCursor()->setCoordinates(currentHex->getGridInfo());
				Selection::Instance()->setHex(currentHex);
				//cout << "Pos: (" << currentHex->getGridInfo().getPosColumn() << ", " << currentHex->getGridInfo().getPosRow() << ")"<< endl;
				//pair de float selon la position en pixel de la case
				auto vect = mt::calculatePixelPosition(Selection::Instance()->getCursor()->getObjectCoordinates().getPosColumn(), Selection::Instance()->getCursor()->getObjectCoordinates().getPosRow());
				if (vect.y+65 > MyView::Instance()->getCenter().y+MyView::Instance()->getSize().y/2)
				{
					MyView::Instance()->move(0,128);
					MyView::Instance()->check();
				}
			}
		}
		return true;  
#endif //Down
	}
	return false;
}

void States::handleRealtimeInputTemplate()
{
	//default nothing
	handleRealtimeInputSpecific();
	MyView::Instance()->check();
}

void States::handleRealtimeInputSpecific()
{
	//default nothing
}


//Operator Overload
