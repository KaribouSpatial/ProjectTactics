//Includes
#include "TEMPLATE_SINGLETON.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
singletonName* singletonName::_instance = nullptr;

//Class Definition
singletonName::singletonName()
{
}

singletonName::~singletonName()
{
	_instance = nullptr;
}

void singletonName::erase()
{
	delete _instance;
}

//Singleton specific
singletonName* singletonName::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new singletonName();
	}
	return _instance;
}


//Access Method

//Modifying method

//Function

//Operator Overload