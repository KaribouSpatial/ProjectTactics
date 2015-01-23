#pragma once

//Includes
#include <vector>
#include <string>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
template<class a>
class Data
{
public:

	//Constructor & Destructor
	Data()
	{
	};

	template<class b>
	Data(b newData)
	{
		if(typeid(b()) == typeid(vector<mt::binUnitStruct>()))
		{
			unsigned size = newData.size();
			data_.resize(size);
			for ( unsigned i_inc = 0; i_inc < size; ++i_inc)
			{
				data_[i_inc] = newData[i_inc];
			}
		} else {
		}
	};

	~Data()
	{
	};

	//Access Methods
	//Modifying methods

	//Functions

	//Operator Overload
	template<class b>
	Data& operator=(b newData)
	{
		data_.resize(newData.size());
		for ( int i_inc = 0; i_inc < data_.size(); ++i_inc)
		{
			data_[i_inc] = newData[i_inc];
		}
	};

	vector<a> operator()() const
	{
		return data_;
	};

	a operator[](int offset) const
	{
		return data_[offset];
	};

private:

	//Private Functions

	//Private Attributes
	vector<a> data_;
};
