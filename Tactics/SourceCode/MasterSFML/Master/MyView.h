#pragma once

//Includes
#include <iostream>

#include <SFML\Graphics.hpp>

//Namespace
using namespace std;

//Defines

//Const

//Typedef

//Class Declaration
class MyView: public sf::View
{
public:
	//Singleton specific
	static MyView* Instance();
	void erase();

	//Destructor
	~MyView();
	//Access Methods
	
	//Modifying methods

	//Functions
	//Called to make sure the view does not move out of the screen
	void check();
	//Operator Overload

	//Attributes
	float topMin;
	float topMax;
	float leftMin;
	float leftMax;
	
protected: 
	//Constructor
	MyView();

private:

	//Private Functions

	//Private Attributes

	//Singleton specific
	static MyView* _instance; 
};
