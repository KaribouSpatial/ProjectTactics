#pragma once



//Includes
#include <thread>           //thread
#include <functional>       //bind
#include <string>           //string
#include <iostream>         //cout+cin
#include <fstream>          //filestream
#include <vector>           //vectors
#include <list>             //lists
#include <assert.h>			//assert(bool)

#include <Windows.h>        //OutputDebugString("My output string");
#include <stdlib.h>         //_CrtDumpMemoryLeaks();
#include <crtdbg.h>	        //_CrtDumpMemoryLeaks();

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

//my namespaces
#include "mt.h"
//#include "Tests.h"


//my classes
#include "Map.h"
#include "Hex.h"
#include "Object.h"
#include "Unit.h"
#include "UnitProperties.h"
#include "Data.h"
#include "TextureLoader.h"
#include "MyView.h"
#include "Selection.h"
#include "World.h"
#include "Player.h"

//Namespace
using namespace std;

//Defines


//Const

//Prototypes

//Typedef


//Class Declaration
class Game
{
public:
	/********
	*Test
	*
	vector<long long> clockTests;
	//End of test*/

	//Constructor
	Game();
	//Destructor
	~Game();

	//Access Method
	const sf::RenderWindow& getWindow() const;

	//Modifying method

	//Function
	void run();

private:

	//Private Functions
	//Creates a Window of parameter sf::style, based on the VideoMode::Resolution attribute
	void initWindow(short style);

	//Update Logic
	void update(sf::Time dt);

	//Event Handling Logic, deleguates to Player class
	void eventHandle();
	bool handleGameEvents(sf::Event& event);
	bool handleKeyGameEvents(sf::Event::KeyEvent key, bool isPressed);

	//rendering functions, it draws to the screen
	void render();

	//Private Threads
	

	//Private Attributes
	mt::Toggle isPaused_;
	sf::VideoMode resolution;

	DataLoader loadedData_;
	TextureLoader textureHolder_;

	sf::RenderWindow window_;


};