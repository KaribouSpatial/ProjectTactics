//Includes
#include "UnitProperties.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
UnitProperties::UnitProperties()
{
	name_.resize(20);
	for each(short& value in unitProperties_)
		value = 0;
}


UnitProperties::~UnitProperties()
{

}

//Access Methods
string UnitProperties::getName() const
{
	return name_;
}

short UnitProperties::get(mt::Properties::Properties number) const
{
	return unitProperties_[number];
}

//Modifying Methods
void UnitProperties::setName(string name)
{
	name_ = name;
}

void UnitProperties::set(mt::Properties::Properties number,short value)
{
	unitProperties_[number] = value;
}

//Functions

//Operator Overloads
UnitProperties& UnitProperties::operator=(const UnitProperties& unitProperties)
{
	name_ = unitProperties.name_;
	for ( int i_inc = 0 ; i_inc < mt::Properties::PropertiesNumber ; ++i_inc)
	{
		unitProperties_[i_inc] = unitProperties.unitProperties_[i_inc];
	}
	return *this;
}

bool UnitProperties::operator==(const UnitProperties unitProperties) const
{
	name_ == unitProperties.name_;

	for ( int i_inc = 0 ; i_inc < mt::Properties::PropertiesNumber ; ++i_inc)
	{
		if (unitProperties_[i_inc] != unitProperties.unitProperties_[i_inc])
			return false;
	}
	return true;

}

