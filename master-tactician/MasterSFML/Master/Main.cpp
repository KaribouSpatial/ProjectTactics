#pragma once
//Preprocessor #ifDefines
#define SFML
#undef TESTBLOCK
#undef CREATEUNIT

//Constant defines
#define TODO

//Macros

//Fancy Preprocessor Commands & Includes
#if 1 
//Includes
//basic
#include <string>           //string
#include <iostream>         //cout+cin
#include <fstream>          //filestream
#include <vector>           //vectors
#include <list>             //lists
#include <assert.h>	        //assert(bool)

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
#include "Game.h"
#include "Map.h"
#include "Hex.h"
#include "Object.h"
#include "Unit.h"
#include "UnitProperties.h"
#include "Data.h"
#include "DataLoader.h"

#endif

//Namespace
using namespace std;
//Const

//Prototypes


int main()
{
	OutputDebugString("\n********************MemoryLeak Start********************\n");
	_CrtDumpMemoryLeaks();
	OutputDebugString("\n*********************MemoryLeak End*********************\n");

	//Launches the game
	
	try{
		Game game;
		game.run();
	}
	catch(runtime_error error){
		cout << endl << error.what() << endl;
	};

	OutputDebugString("\n********************MemoryLeak Start********************\n");
	_CrtDumpMemoryLeaks();
	OutputDebugString("\n*********************MemoryLeak End*********************\n");

	system("pause");

	return SUCCESS;
}


