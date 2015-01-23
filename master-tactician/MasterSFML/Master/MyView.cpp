//Includes
#include "MyView.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
MyView* MyView::_instance = nullptr;

//Class Definition
//Constructor & Destructor
MyView::MyView()
{
}

MyView::~MyView()
{
	cout << "~" << typeid(*this).name() << endl;
}

//Singleton specific
MyView* MyView::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new MyView();
	}
	return _instance;
}

void MyView::erase()
{
	delete _instance;
	_instance = nullptr;
}

//Access Methods

//Modifying methods

//Functions

void MyView::check()
{
	if (getCenter().x > leftMax)
		setCenter(leftMax, getCenter().y);
	else if (getCenter().x < leftMin)
		setCenter(leftMin, getCenter().y);

	if (getCenter().y > topMax)
		setCenter(getCenter().x, topMax);
	else if (getCenter().y < topMin)
		setCenter(getCenter().x, topMin);
}

//Operator Overloads
