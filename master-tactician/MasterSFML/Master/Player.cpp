//Includes
#include "Player.h"
#include "States_Selecting.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
Player* Player::_instance = nullptr;

//Class Definition
Player::Player()
{
	state_ = States_Selecting::Instance();
}

Player::~Player()
{
	if (state_ != nullptr)
	{
		delete state_;
		state_ = nullptr;
	}
	cout << "~" << typeid(*this).name() << endl;
}

//Singleton specific
Player* Player::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new Player();
	}
	return _instance;
}

void Player::erase()
{
	delete _instance;
	_instance = nullptr;
}

//Access Method
const States* Player::getState() const
{
	return state_;
}

//Modifying method
void Player::setState(States* state)
{
	state_->erase();
	state_ = state;
}

//Function
void Player::handleEvent(const sf::Event& event)
{
	// check the type of the event...
	switch (event.type)
	{
		// Key pressed
	case sf::Event::KeyPressed:
		//cout << "press: " << event.key.code << endl;
		handlePlayerInput(event.key, true);
		break;

		// Key released
	case sf::Event::KeyReleased:
		//cout << "release: " << event.key.code << endl;
		handlePlayerInput(event.key, false);
		break;

	case sf::Event::MouseButtonPressed:
		/*cout << "x: " << event.mouseButton.x << endl;
		cout << "y: " << event.mouseButton.y << endl;*/
		break;

	case sf::Event::MouseButtonReleased:
		/*cout << "x: " << event.mouseButton.x << endl;
		cout << "y: " << event.mouseButton.y << endl;*/
		break;

	case sf::Event::MouseMoved:
		/*cout << "mouse x: " << event.mouseMove.x << endl;
		cout << "mouse y: " << event.mouseMove.y << endl;*/
		break;

	default:
		break;
	}
}	

void Player::handleRealtimeInput()
{
	state_->handleRealtimeInputTemplate();
}

void Player::handlePlayerInput(sf::Event::KeyEvent key, bool isPressed)
{
	state_->handlePlayerInputTemplate(key, isPressed);
}
//Operator Overload
