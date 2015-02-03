//Includes
#include "States_FreeCamera.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
States_FreeCamera* States_FreeCamera::_instance = nullptr;

//Class Definition
States_FreeCamera::States_FreeCamera()
{
}

States_FreeCamera::~States_FreeCamera()
{
	_instance = nullptr;
}

void States_FreeCamera::erase()
{
	delete _instance;
}

//Singleton specific
States_FreeCamera* States_FreeCamera::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new States_FreeCamera();
	}
	return _instance;
}

//Access Method

//Modifying method

//Function
bool States_FreeCamera::handlePlayerInputSpecific(sf::Event::KeyEvent key, bool isPressed)
{
	switch (key.code)
	{
	case sf::Keyboard::Key::Return:
#if 1
		if (isPressed)
		{
			//selection position is the upper left corner
			MyView::Instance()->setCenter(Selection::Instance()->getSprite().getPosition().x+64, Selection::Instance()->getSprite().getPosition().y+32);
			Selection::Instance()->getCursor()->setColor(mt::Overlay::Color::White);
			Player::Instance()->setState(States_Selecting::Instance());
			cout << "State: Selecting" << endl;
		}
		return true;
#endif //Return(enter)

	case sf::Keyboard::Key::BackSpace: //fallthrough
	case sf::Keyboard::Key::Escape:
		return true;
	}
	return false;	
}

bool States_FreeCamera::handlePlayerInputArrows(sf::Event::KeyEvent key, bool isPressed)
{
	//do nothing
	return false;
}

void States_FreeCamera::handleRealtimeInputSpecific()
{
	sf::Vector2f freeCamera(0,0);
	bool horizontal = false;
	bool vertical = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		freeCamera.x -= 120*mt::SecondPerFrame.asSeconds();
		horizontal =! horizontal;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		freeCamera.x += 120*mt::SecondPerFrame.asSeconds();
		horizontal =! horizontal;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		freeCamera.y -= 120*mt::SecondPerFrame.asSeconds();
		vertical =! vertical;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		freeCamera.y += 120*mt::SecondPerFrame.asSeconds();
		vertical =! vertical;
	}
	if (vertical && horizontal)
		freeCamera /= 1.414f; //1.414 = ~mt::sqrt(2)
	MyView::Instance()->move(freeCamera);
}

//Operator Overload