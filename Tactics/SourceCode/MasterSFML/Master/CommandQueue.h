#pragma once

//Includes
#include "mt.h"
#include "SceneNode.h"
#include "Command.h"

#include <queue>
//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class CommandQueue
{
public:

	//Constructor
	CommandQueue();

	//Destructor
	~CommandQueue();

	//R-only access

	//R-W access
	
	//Modifying method

	//Function
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;

	//Operator Overload

private:

	//Private Functions

	//Private Attributes
	queue<Command> queue_;
};
