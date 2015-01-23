#pragma once

//Includes
#include "mt.h"

#include <string>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration

class UnitProperties
{

public:

	//Constructor & Destructor
	UnitProperties();
	template<class t>
	UnitProperties(const t& properties)
	{
		name_.resize(20);
		for ( int i_inc = 0 ; i_inc < 20 ; ++i_inc)
		{
			name_[i_inc] = properties.name[i_inc];
		}

		for ( int properties_inc = 0 ; properties_inc < mt::Properties::PropertiesNumber ; ++properties_inc)
		{
			unitProperties_[properties_inc] = properties.properties[properties_inc];
		}
	}

	~UnitProperties();
#if 1
	//Access Methods
	string getName() const;
	short get(mt::Properties::Properties number) const;

	//Modifying Methods
	void setName(string name);
	void set(mt::Properties::Properties number,short value);

#endif
	//Functions
	
	//Operator Overload
	UnitProperties& operator=(const UnitProperties& unitProperties);
	bool UnitProperties::operator==(const UnitProperties unitProperties) const;

private:

	//Private Functions

	//Private Attributes
	string name_;
	short unitProperties_[mt::Properties::PropertiesNumber];

};
