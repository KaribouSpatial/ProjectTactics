//Includes
#include "Pathing.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
Pathing::Pathing()
{
	for each(bool& pathing in pathing_)
		pathing = 0;
}

Pathing::Pathing(mt::BinPathingStruct pathing)
{
	for ( int i_inc = 0; i_inc < mt::PathingNumber; ++i_inc)
	{
		pathing_[i_inc] = pathing[mt::Pathing(i_inc)];
	}
}

Pathing::~Pathing()
{

}


//Access Methods
bool Pathing::get(mt::Pathing pathing) const
{
	return pathing_[pathing];
}



//Modifying methods
void Pathing::setAll(const mt::BinPathingStruct pathing)
{
	for ( int i_inc = 0; i_inc < mt::PathingNumber; ++i_inc)
	{
		pathing_[i_inc] = pathing[mt::Pathing(i_inc)];
	}
}

void Pathing::set(const mt::Pathing number, const bool value)
{
	pathing_[number] = value;
}

//Functions

//Private Functions

//Operator Overloads
Pathing& Pathing::operator=(const Pathing& pathing)
{
	for ( int i_inc = 0; i_inc < mt::PathingNumber; ++i_inc)
	{
		pathing_[i_inc] = pathing[mt::Pathing(i_inc)];
	}
	return *this;
}

Pathing& Pathing::operator=(const mt::BinPathingStruct pathing)
{
	for ( int i_inc = 0; i_inc < mt::PathingNumber; ++i_inc)
	{
		pathing_[i_inc] = pathing[mt::Pathing(i_inc)];
	}
	return *this;
}

bool Pathing::operator[](const mt::Pathing pathing) const
{
	return pathing_[pathing];
}

