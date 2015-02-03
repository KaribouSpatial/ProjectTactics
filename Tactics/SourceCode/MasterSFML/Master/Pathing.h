#pragma once

//Includes
#include "mt.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class Pathing
{
public:

	//Constructor & Destructor
	Pathing();
	Pathing(mt::BinPathingStruct pathing);
	~Pathing();
	
	//Access Methods
	bool Pathing::get(mt::Pathing pathing) const;
	
	//Modifying methods
	void setAll(const mt::BinPathingStruct pathing);
	void set(const mt::Pathing number,const bool value);

	//Functions

	//Operator Overload
	Pathing& operator=(const Pathing& pathing);
	Pathing& operator=(const mt::BinPathingStruct pathing);
	bool operator[](const mt::Pathing path) const;


private:

	//Private Functions

	//Private Attributes
	bool pathing_[mt::PathingNumber];
	

};
