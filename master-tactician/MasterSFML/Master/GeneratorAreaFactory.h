#pragma once

//Includes
#include "GeneratorArea.h"

#include <iostream>
#include <array>

//Namespace
using namespace std;

//Defines
#define OUT

//Const

//Prototypes

//Class Prototypes
class GeneratorArea;

//Class Declaration
class GeneratorAreaFactory 
{ 
public:
	//Singleton specific
	static GeneratorAreaFactory* Instance();
	void erase();

	//Destructor
	~GeneratorAreaFactory();

	//R-only access

	//R-W access

	//Modifying method

	//Function
	array<GeneratorArea*,mt::TypeArea::nbTypeArea>* createGenerators();

	//Operator Overload

protected: 
	//Constructor
	GeneratorAreaFactory();

private: 
	//Private Function

	//Private Attribute

	//Singleton specific
	static GeneratorAreaFactory* _instance; 
}; 
