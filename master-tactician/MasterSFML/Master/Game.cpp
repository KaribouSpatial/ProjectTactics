//Includes
#include "Game.h"
//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
Game::Game() :
	//renderingThread_(&Game::renderingThread, this),
	resolution(800,600),
	textureHolder_(&loadedData_)
{
	loadedData_.loadAll();
	textureHolder_.loadAll();

	window_.setVerticalSyncEnabled(true);
	//window_.setFramerateLimit(60);

	World::Create(&window_, &loadedData_, &textureHolder_);

	initWindow(sf::Style::Default);
}

Game::~Game()
{
	cout << "~" << typeid(*this).name() << endl;
	World::Instance()->erase();
	MyView::Instance()->erase();
	Player::Instance()->erase();
	Selection::Instance()->erase();
}

//Access Methods
const sf::RenderWindow& Game::getWindow() const
{
	return window_;
}
//Modifying methods

//Functions
void Game::run()
{
	cout << "Game is running!" << endl;
	sf::Clock clock;
	sf::Time dt = sf::Time::Zero;
	update(mt::SecondPerFrame);
	
	while (window_.isOpen())
	{
		eventHandle();
		dt += clock.restart();
		while (dt > mt::SecondPerFrame)
		{
			dt -= mt::SecondPerFrame;
			eventHandle();
			if (!isPaused_())
			{
				update(mt::SecondPerFrame); 
			}
		}

		if (!isPaused_())
		{
			//REMOVE COMMENTS FOR CLOCK TEST
			//sf::Clock testClock;
			//REMOVE COMMENTS FOR CLOCK TEST

			render();

			//REMOVE COMMENTS FOR CLOCK TEST 
			/*sf::Time testTime = testClock.restart();
			if (testTime.asMicroseconds() > 16666)
			clockTests.push_back(testTime.asMicroseconds());
			//cout << "Total Render timer: " << testTime.asMicroseconds() << endl;*/
			//REMOVE COMMENTS FOR CLOCK TEST
		}
		else
		{
			window_.clear(sf::Color::Black);
			window_.display();
		}
	}
}

//Private Functions
void Game::render()
{
	//clear previous frame
	window_.clear(sf::Color::Black);

	//drawing units
	try{
		World::Instance()->draw();

		window_.setView(window_.getDefaultView());
		//window_.draw(TODO:GUI);

	} catch (exception e){
		cout << "Exception caught: " << e.what() << endl;

	} catch(...) {
		cout << "Exception caught when drawing!" << endl;
	}

	//TODO: draw something else?

	//display the frame
	window_.display();

	return;
}

void Game::update(sf::Time dt)
{
	World::Instance()->update(dt);
}

void Game::eventHandle()
{
	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	window_.setKeyRepeatEnabled(true);
	
	while (window_.pollEvent(event))
	{	
		if(!handleGameEvents(event))
			Player::Instance()->handleEvent(event);
	}
	Player::Instance()->handleRealtimeInput();
}

bool Game::handleGameEvents(sf::Event& event)
{
	switch (event.type)
		{
		case sf::Event::LostFocus:
			cout << "Lost Focus" << endl;
			if (!isPaused_.toggled)
				isPaused_.toggle();
			break;

		case sf::Event::GainedFocus:
			cout << "Gained Focus" << endl;
			if (isPaused_.toggled)
			{
				isPaused_.toggle();
				isPaused_.toggled = false;
			}
			break;

			// we don't process other types of events
		case sf::Event::Resized:
			if (event.size.width <= sf::VideoMode::getFullscreenModes()[0].width &&
				event.size.height <= sf::VideoMode::getFullscreenModes()[0].height)
			{
				cout << "Resizing to: " << event.size.width << 'x' << event.size.height << endl;
				resolution.width = event.size.width;
				resolution.height = event.size.height;
				resolution.bitsPerPixel = resolution.bitsPerPixel;
				initWindow(sf::Style::Default); 
			}
			else
			{
				cout << "Resizing to: 800x600" << endl;
				resolution.width = 800;
				resolution.height = 600;
				resolution.bitsPerPixel = resolution.bitsPerPixel;
				initWindow(sf::Style::Default); 
			}
			break;

		case sf::Event::Closed:
			window_.close();
			break;

		case sf::Event::KeyPressed:
			//cout << "press: " << event.key.code << endl;
			return handleKeyGameEvents(event.key, true);
			break;

			// Key released
		case sf::Event::KeyReleased:
			//cout << "release: " << event.key.code << endl;
			return handleKeyGameEvents(event.key, false);
			break;

		default:
			break;

		}
	return false;
}

bool Game::handleKeyGameEvents(sf::Event::KeyEvent key, bool isPressed)
{
	switch (key.code)
	{
	case sf::Keyboard::Key::Return:
		if(isPressed)
		{
			if (key.alt)
			{
				
				if (resolution != sf::VideoMode::getFullscreenModes()[0])
				{
					resolution = sf::VideoMode::getFullscreenModes()[0];
					initWindow(sf::Style::Fullscreen);
					return true;
				}
				else
				{
					resolution.width = 800;
					resolution.height = 600;
					resolution.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
					initWindow(sf::Style::Default);
					return true;
				}
			}
		}
		break;
	case sf::Keyboard::Key::R:
		if (!isPressed && key.alt)
		{
			cout << "Fullscreen? (y/n)" << endl;
			char answer;
			cin >> answer;
			if (answer == 'n')
			{
				cout << "Resolution X: " << endl;
				if (!(cin >> resolution.width)) {
					cin.clear();
					cin.ignore(20, '\n');
					cout << "Error" << endl;
					break;
				}
				cout << "Resolution Y: " << endl;
				if (!(cin >> resolution.height)) {
					cin.clear();
					cin.ignore(20, '\n');
					cout << "Error" << endl;
					break;
				}
				resolution.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
				initWindow(sf::Style::Default^sf::Style::Resize);
				break;
			}
			else{
				resolution = sf::VideoMode::getFullscreenModes()[0];
				initWindow(sf::Style::Fullscreen);
			}
			return true;
		}
		break;

	case sf::Keyboard::Key::U:
		if (key.control && !isPressed)
		{
			Map::Instance()->toggleContour();
			return true;
		}
		break;

	case sf::Keyboard::Key::RBracket:
		if (isPressed)
		{
			MyView::Instance()->setSize(
				MyView::Instance()->getSize().x-128,
				MyView::Instance()->getSize().y-64);
			MyView::Instance()->leftMin -= 64;
			MyView::Instance()->topMin -= 32;
			MyView::Instance()->leftMax += 64;
			MyView::Instance()->topMax += 32;
			if (MyView::Instance()->getSize().x <= Map::Instance()->getWidth()*32 ||
				MyView::Instance()->getSize().y <= Map::Instance()->getHeight()*16)
			{
				MyView::Instance()->setSize(
					MyView::Instance()->getSize().x+128,
					MyView::Instance()->getSize().y+64);
				MyView::Instance()->leftMin += 64;
				MyView::Instance()->topMin += 32;
				MyView::Instance()->leftMax -= 64;
				MyView::Instance()->topMax -= 32;
			}
			return true;
		}
		break;

	case sf::Keyboard::Key::BackSlash:
		if (isPressed)
		{
			MyView::Instance()->setSize(
				MyView::Instance()->getSize().x+128,
				MyView::Instance()->getSize().y+64);
			MyView::Instance()->leftMin += 64;
			MyView::Instance()->topMin += 32;
			MyView::Instance()->leftMax -= 64;
			MyView::Instance()->topMax -= 32;
			if ((MyView::Instance()->getSize().x >= (Map::Instance()->getWidth()-2)*128) || 
				(MyView::Instance()->getSize().y >= (Map::Instance()->getHeight()-2)*49))
			{
				MyView::Instance()->setSize(
					MyView::Instance()->getSize().x-128,
					MyView::Instance()->getSize().y-64);
				MyView::Instance()->leftMin -= 64;
				MyView::Instance()->topMin -= 32;
				MyView::Instance()->leftMax += 64;
				MyView::Instance()->topMax += 32;
			}
			return true;
		}
		break;

	case sf::Keyboard::Key::F4:
		if (key.alt)
		/*{
			sf::Event close;
			close.type = sf::Event::Closed;
			handleGameEvents(close);
		}*/
			window_.close();
		break;

	default:
		break;
	}
	return false;
}
//Window initiation
void Game::initWindow(short style)
{
	//window_.setVisible(false);

	if (style > 8)
		style = sf::Style::Fullscreen;
	else if (style < 0)
		style = sf::Style::Default;

	window_.close();
	window_.create(resolution, "Master-Tactician", style);
	window_.setVerticalSyncEnabled(true);

	MyView::Instance()->reset(sf::FloatRect(0, 0, (float)resolution.width, (float)resolution.height));

	MyView::Instance()->topMin = 32.0f+resolution.height/2.0f;
	MyView::Instance()->topMax = MAP_SIZE_Y * 49.0f - resolution.height/2.0f;

	while ((int)(MyView::Instance()->topMax-MyView::Instance()->topMin)%49)
	{
		--(MyView::Instance()->topMax);
	}

	MyView::Instance()->leftMin = 64.0f+resolution.width/2.0f;
	MyView::Instance()->leftMax = MAP_SIZE_X * 128.0f - resolution.width/2.0f;

	while ((int)(MyView::Instance()->leftMax-MyView::Instance()->leftMin) % 128)
	{
		--(MyView::Instance()->leftMax);
	}

	MyView::Instance()->setCenter(MyView::Instance()->leftMin, MyView::Instance()->topMin);
	window_.setVisible(true);
}
