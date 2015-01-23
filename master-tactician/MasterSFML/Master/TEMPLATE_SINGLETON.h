#pragma once

//Includes

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class singletonName 
{ 
public:
	//Singleton specific
	static singletonName* Instance();
	void erase();

	//Destructor
	~singletonName();

	//R-only access

	//R-W access

	//Modifying method

	//Function

	//Operator Overload

protected: 
	//Constructor
	singletonName();

private: 
	//Private Function

	//Private Attribute

	//Singleton specific
	static singletonName* _instance; 
}; 
