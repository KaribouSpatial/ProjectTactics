//Includes
#include "CommandQueue.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
CommandQueue::CommandQueue()
{
}
CommandQueue::~CommandQueue()
{
}

//Access Method

//Modifying method

//Function
void CommandQueue::push(const Command& command)
{
	queue_.push(command);
}


Command CommandQueue::pop()
{
	Command command = queue_.back();
	queue_.pop();
	return command;
}


bool CommandQueue::isEmpty() const
{
	if (queue_.size() == 0)
		return true;
	else return false;
}


//Operator Overload
