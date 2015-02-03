#pragma once

//Includes
#include "GeneratorArea.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class GeneratorCornerLine: public GeneratorArea
{
public:

	//Constructor
	GeneratorCornerLine();

	//Destructor
	~GeneratorCornerLine();

	//R-only access

	//R-W access
	
	//Modifying method

	//Function
	//Requires: width_[2,3], lenght_, direction_
	Area generateArea(Hex* center, GeneratorParameters param) override;

	//Operator Overload

private:

	//Private Function
	Area generateCornerLine(Hex* center, GeneratorParameters param);

	//Private Attribute

};
