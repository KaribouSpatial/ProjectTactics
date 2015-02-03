#pragma once

//Includes

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class GeneratorParameters
{
public:

	//Constructor
	GeneratorParameters(
		unsigned int lenght = 2, 
		unsigned int width = 1, 
		unsigned int direction = 0,
		bool isLarger = false,
		unsigned int firstDirection = 0
		):
	lenght_(lenght),
		width_(width),
		direction_(direction),
		firstDirection_(firstDirection),
		isLarger_(isLarger)
	{
		//protection (direction ranges 0-5)
		if (direction_ > 6)
			direction_ %= 6;
		if (firstDirection_ > 6)
			firstDirection_ %= 6;
	};

	//Destructor
	~GeneratorParameters() {};

	//R-only access

	//R-W access
	
	//Modifying method

	//Function
	
	//Operator Overload
	
	unsigned int lenght_;
	unsigned int width_;
	
	unsigned int direction_;
	unsigned int firstDirection_;

	bool isLarger_;
};
