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
class GeneratorCircle: public GeneratorArea
{
public:

	//Constructor
	GeneratorCircle();

	//Destructor
	~GeneratorCircle();

	//R-only access

	//R-W access
	
	//Modifying method

	//Function
	//Requires: width_
	Area generateArea(Hex* center, GeneratorParameters param) override;

	//Operator Overload

private:

	//Private Function
	Area generateCircle(Hex* center, GeneratorParameters param);

	//Private Attribute

};
