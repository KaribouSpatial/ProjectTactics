#pragma once

//Includes
#include "Hex.h"
#include "GeneratorParameters.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes
class Hex;

//Class Declaration
class GeneratorArea
{
protected:
	//Typedef
	typedef vector<Hex*> Area;

public:
	//Destructor
	virtual ~GeneratorArea() = 0 {};

	//R-only access

	//R-W access
	
	//Modifying method

	//Function
	virtual Area generateArea(Hex* center, GeneratorParameters param) = 0;

	//Operator Overload

protected:
	//Constructor
	GeneratorArea() {};

private:

	//Private Function

	//Private Attribute

};
